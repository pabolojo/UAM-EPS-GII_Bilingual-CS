--------------------------------------------------------------------------------
-- Procesador MIPS con pipeline curso Arquitectura 2020-2021
--
-- (INCLUIR AQUI LA INFORMACION SOBRE LOS AUTORES)
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity processor is
   port(
      Clk         : in  std_logic; -- Reloj activo en flanco subida
      Reset       : in  std_logic; -- Reset asincrono activo nivel alto
      -- Instruction memory
      IAddr      : out std_logic_vector(31 downto 0); -- Direccion Instr
      IDataIn    : in  std_logic_vector(31 downto 0); -- Instruccion leida
      -- Data memory
      DAddr      : out std_logic_vector(31 downto 0); -- Direccion
      DRdEn      : out std_logic;                     -- Habilitacion lectura
      DWrEn      : out std_logic;                     -- Habilitacion escritura
      DDataOut   : out std_logic_vector(31 downto 0); -- Dato escrito
      DDataIn    : in  std_logic_vector(31 downto 0)  -- Dato leido
   );
end processor;

architecture rtl of processor is

  component alu
    port(
      OpA : in std_logic_vector (31 downto 0);
      OpB : in std_logic_vector (31 downto 0);
      Control : in std_logic_vector (3 downto 0);
      Result : out std_logic_vector (31 downto 0);
      Zflag : out std_logic
    );
  end component;

  component reg_bank
     port (
        Clk   : in std_logic; -- Reloj activo en flanco de subida
        Reset : in std_logic; -- Reset as�ncrono a nivel alto
        A1    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd1
        Rd1   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd1
        A2    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd2
        Rd2   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd2
        A3    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Wd3
        Wd3   : in std_logic_vector(31 downto 0);  -- Dato de entrada Wd3
        We3   : in std_logic -- Habilitaci�n de la escritura de Wd3
     );
  end component reg_bank;

  component control_unit
     port (
        -- Entrada = codigo de operacion en la instruccion:
        OpCode   : in  std_logic_vector (5 downto 0);
        -- Seniales para el PC
        Branch   : out  std_logic; -- 1 = Ejecutandose instruccion branch
        -- Seniales relativas a la memoria
        MemToReg : out  std_logic; -- 1 = Escribir en registro la salida de la mem.
        MemWrite : out  std_logic; -- Escribir la memoria
        MemRead  : out  std_logic; -- Leer la memoria
        -- Seniales para la ALU
        ALUSrc   : out  std_logic;                     -- 0 = oper.B es registro, 1 = es valor inm.
        ALUOp    : out  std_logic_vector (2 downto 0); -- Tipo operacion para control de la ALU
        -- Seniales para el GPR
        RegWrite : out  std_logic; -- 1=Escribir registro
        RegDst   : out  std_logic;  -- 0=Reg. destino es rt, 1=rd

        Jump     : out  std_logic
     );
  end component;

  component alu_control is
   port (
      -- Entradas:
      ALUOp  : in std_logic_vector (2 downto 0); -- Codigo de control desde la unidad de control
      Funct  : in std_logic_vector (5 downto 0); -- Campo "funct" de la instruccion
      -- Salida de control para la ALU:
      ALUControl : out std_logic_vector (3 downto 0) -- Define operacion a ejecutar por la ALU
   );
 end component alu_control;

  signal Alu_Op2      : std_logic_vector(31 downto 0);
  signal ALU_Igual    : std_logic;
  signal AluControl   : std_logic_vector(3 downto 0);
  signal reg_RD_data  : std_logic_vector(31 downto 0);
  signal reg_RD       : std_logic_vector(4 downto 0);

  signal PC_next        : std_logic_vector(31 downto 0);
  signal PC_reg         : std_logic_vector(31 downto 0);
  signal PC_plus4       : std_logic_vector(31 downto 0);

  -- signal Instruction    : std_logic_vector(31 downto 0); -- La instrucción desde lamem de instr
  signal Inm_ext        : std_logic_vector(31 downto 0); --Lparte baja de la instrucción extendida de signo
  signal reg_RS, reg_RT : std_logic_vector(31 downto 0);

  signal dataIn_Mem     : std_logic_vector(31 downto 0); --From Data Memory
  signal Addr_Branch    : std_logic_vector(31 downto 0);

  signal Ctrl_Jump, Ctrl_Branch, Ctrl_MemWrite, Ctrl_MemRead,  Ctrl_ALUSrc, Ctrl_RegDest, Ctrl_MemToReg, Ctrl_RegWrite : std_logic;
  signal Ctrl_ALUOP     : std_logic_vector(2 downto 0);

  signal Addr_Jump      : std_logic_vector(31 downto 0);
  signal Addr_Jump_dest : std_logic_vector(31 downto 0);
  signal desition_Jump  : std_logic;
  signal Alu_Res        : std_logic_vector(31 downto 0);

  -- IF/ID

  signal Instruction_IFID : std_logic_vector(31 downto 0);
  signal PC_plus4_IFID    : std_logic_vector(31 downto 0);
  signal enable_IFID      : std_logic;

  -- ID/EX
  signal Branch_IDEX      : std_logic;
  signal MemToReg_IDEX    : std_logic;
  signal MemWrite_IDEX    : std_logic;
  signal MemRead_IDEX     : std_logic;
  signal ALUSrc_IDEX      : std_logic;
  signal ALUOp_IDEX       : std_logic_vector (2 downto 0);
  signal RegWrite_IDEX    : std_logic;
  signal RegDst_IDEX      : std_logic;
  signal Jump_IDEX        : std_logic;
  signal Jump_Address_IDEX    : std_logic_vector(31 downto 0);

  signal PC_plus4_IDEX    : std_logic_vector(31 downto 0);
  signal Reg1_IDEX        : std_logic_vector(31 downto 0);
  signal Reg2_IDEX        : std_logic_vector(31 downto 0);
  signal Inmediate_IDEX   : std_logic_vector(31 downto 0);
  signal Instruction_IDEX : std_logic_vector(20 downto 11);

  signal enable_IDEX      : std_logic;

  -- EX/MEM
  signal Branch_EXMEM     : std_logic;
  signal MemToReg_EXMEM   : std_logic;
  signal MemWrite_EXMEM   : std_logic;
  signal MemRead_EXMEM    : std_logic;
  signal RegWrite_EXMEM   : std_logic;
  signal Jump_EXMEM       : std_logic;

  signal Jump_Address_EXMEM    : std_logic_vector(31 downto 0);
  signal Zero_EXMEM       : std_logic;
  signal Alu_result_EXMEM : std_logic_vector(31 downto 0);
  signal Reg2_EXMEM       : std_logic_vector(31 downto 0);
  signal reg_RD_EXMEM     : std_logic_vector(4 downto 0);

  signal enable_EXMEM     : std_logic;

  -- MEM/WB
  signal MemToReg_MEMWB   : std_logic;
  signal RegWrite_MEMWB   : std_logic;

  signal Alu_result_MEMWB : std_logic_vector(31 downto 0);
  signal Mem_data_MEMWB   : std_logic_vector(31 downto 0);
  signal reg_RD_MEMWB     : std_logic_vector(4 downto 0);

  signal enable_MEMWB     : std_logic;

begin

  PC_next <= Jump_Address_EXMEM when desition_Jump = '1' else PC_plus4;

  PC_reg_proc: process(Clk, Reset)
  begin
    if Reset = '1' then
      PC_reg <= (others => '0');
    elsif rising_edge(Clk) then
      PC_reg <= PC_next;
    end if;
  end process;

  -- IF/ID PROCESS
  IF_ID_proc: process(Clk, Reset, enable_IFID, IDataIn, PC_plus4)
  begin
    if Reset = '1' then
      Instruction_IFID <= (others => '0');
      PC_plus4_IFID <= (others => '0');
    elsif rising_edge(Clk) and enable_IFID = '1' then
      Instruction_IFID <= IDataIn;
      PC_plus4_IFID <= PC_plus4;
    end if;
  end process;

  enable_IFID <= '1';



  -- ID/EX PROCESS
  ID_EX_proc: process(Clk, Reset, enable_IDEX, Ctrl_Branch, Ctrl_MemToReg, Ctrl_MemWrite, Ctrl_MemRead, Ctrl_ALUSrc, Ctrl_ALUOP, Ctrl_RegWrite, Ctrl_RegDest, Ctrl_Jump, Addr_Jump, PC_plus4_IFID, reg_RS, reg_RT, Inm_ext, Instruction_IFID)
  begin
    if Reset = '1' then
      Branch_IDEX      <= '0';
      MemToReg_IDEX    <= '0';
      MemWrite_IDEX    <= '0';
      MemRead_IDEX     <= '0';
      ALUSrc_IDEX      <= '0';
      ALUOp_IDEX       <= (others => '0');
      RegWrite_IDEX    <= '0';
      RegDst_IDEX      <= '0';
      Jump_IDEX        <= '0';
      Jump_Address_IDEX <= (others => '0');
      PC_plus4_IDEX    <= (others => '0');
      Reg1_IDEX        <= (others => '0');
      Reg2_IDEX        <= (others => '0');
      Inmediate_IDEX   <= (others => '0');
      Instruction_IDEX <= (others => '0');
    elsif rising_edge(Clk) and enable_IDEX = '1' then
      Branch_IDEX      <= Ctrl_Branch;
      MemToReg_IDEX    <= Ctrl_MemToReg;
      MemWrite_IDEX    <= Ctrl_MemWrite;
      MemRead_IDEX     <= Ctrl_MemRead;
      ALUSrc_IDEX      <= Ctrl_ALUSrc;
      ALUOp_IDEX       <= Ctrl_ALUOP;
      RegWrite_IDEX    <= Ctrl_RegWrite;
      RegDst_IDEX      <= Ctrl_RegDest;
      Jump_IDEX        <= Ctrl_Jump;
      Jump_Address_IDEX <= Addr_Jump;

      PC_plus4_IDEX    <= PC_plus4_IFID;
      Reg1_IDEX        <= reg_RS;
      Reg2_IDEX        <= reg_RT;
      Inmediate_IDEX   <= Inm_ext;
      Instruction_IDEX <= Instruction_IFID(20 downto 11);
    end if;
  end process;

  enable_IDEX <= '1';



  -- EX/MEM PROCESS
  EX_MEM_proc: process(Clk, Reset, enable_EXMEM, Branch_IDEX, MemToReg_IDEX, MemWrite_IDEX, MemRead_IDEX, RegWrite_IDEX, Jump_IDEX, Addr_Jump_dest, ALU_IGUAL, Alu_Res, Reg2_IDEX, reg_RD)
  begin
    if Reset = '1' then
      Branch_EXMEM     <= '0';
      MemToReg_EXMEM   <= '0';
      MemWrite_EXMEM   <= '0';
      MemRead_EXMEM    <= '0';
      RegWrite_EXMEM   <= '0';
      Jump_EXMEM       <= '0';
      Jump_Address_EXMEM <= (others => '0');
      Zero_EXMEM       <= '0';
      Alu_result_EXMEM <= (others => '0');
      Reg2_EXMEM       <= (others => '0');
      reg_RD_EXMEM     <= (others => '0');
    elsif rising_edge(Clk) and enable_EXMEM = '1' then
      Branch_EXMEM     <= Branch_IDEX;
      MemToReg_EXMEM   <= MemToReg_IDEX;
      MemWrite_EXMEM   <= MemWrite_IDEX;
      MemRead_EXMEM    <= MemRead_IDEX;
      RegWrite_EXMEM   <= RegWrite_IDEX;
      Jump_EXMEM       <= Jump_IDEX;
      Jump_Address_EXMEM <= Addr_Jump_dest;
      Zero_EXMEM       <= ALU_IGUAL;
      Alu_result_EXMEM <= Alu_Res;
      Reg2_EXMEM       <= Reg2_IDEX;
      reg_RD_EXMEM     <= reg_RD;
    end if;
  end process;

  enable_EXMEM <= '1';



  -- MEM/WB PROCESS
  MEM_WB_proc: process(Clk, Reset, enable_MEMWB, MemToReg_EXMEM, RegWrite_EXMEM, Alu_result_EXMEM, dataIn_Mem, reg_RD_EXMEM)
  begin
    if Reset = '1' then
      MemToReg_MEMWB   <= '0';
      RegWrite_MEMWB   <= '0';
      Alu_result_MEMWB <= (others => '0');
      Mem_data_MEMWB   <= (others => '0');
      reg_RD_MEMWB     <= (others => '0');
    elsif rising_edge(Clk) and enable_MEMWB = '1' then
      MemToReg_MEMWB   <= MemToReg_EXMEM;
      RegWrite_MEMWB   <= RegWrite_EXMEM;
      Alu_result_MEMWB <= Alu_result_EXMEM;
      Mem_data_MEMWB   <= dataIn_Mem;
      reg_RD_MEMWB     <= reg_RD_EXMEM;
    end if;
  end process;

  enable_MEMWB <= '1';

  PC_plus4    <= PC_reg + 4;
  IAddr       <= PC_reg;

  RegsMIPS : reg_bank
  port map (
    Clk   => Clk,
    Reset => Reset,
    A1    => Instruction_IFID(25 downto 21),
    Rd1   => reg_RS,
    A2    => Instruction_IFID(20 downto 16),
    Rd2   => reg_RT,
    A3    => reg_RD_MEMWB,
    Wd3   => reg_RD_data,
    We3   => RegWrite_MEMWB
  );

  UnidadControl : control_unit
  port map(
    OpCode   => Instruction_IFID(31 downto 26),
    -- Señales para el PC
    Jump   => Ctrl_Jump,
    Branch   => Ctrl_Branch,
    -- Señales para la memoria
    MemToReg => Ctrl_MemToReg,
    MemWrite => Ctrl_MemWrite,
    MemRead  => Ctrl_MemRead,
    -- Señales para la ALU
    ALUSrc   => Ctrl_ALUSrc,
    ALUOP    => Ctrl_ALUOP,
    -- Señales para el GPR
    RegWrite => Ctrl_RegWrite,
    RegDst   => Ctrl_RegDest
  );

  Inm_ext        <= x"FFFF" & Instruction_IFID(15 downto 0) when Instruction_IFID(15)='1' else
                    x"0000" & Instruction_IFID(15 downto 0);
  Addr_Jump      <= PC_plus4_IFID(31 downto 28) & Instruction_IFID(25 downto 0) & "00";
  Addr_Branch    <= PC_plus4_IDEX + ( Inmediate_IDEX(29 downto 0) & "00");

  -- Ctrl_Jump      <= '0'; --nunca salto incondicional

  desition_Jump  <= Jump_EXMEM or (Branch_EXMEM and Zero_EXMEM);
  Addr_Jump_dest <= Jump_Address_IDEX when Jump_IDEX='1' else
                    Addr_Branch when Branch_IDEX='1' else
                    (others =>'0');

  Alu_control_i: alu_control
  port map(
    -- Entradas:
    ALUOp  => ALUOp_IDEX, -- Codigo de control desde la unidad de control
    Funct  => Inmediate_IDEX(5 downto 0), -- Campo "funct" de la instruccion
    -- Salida de control para la ALU:
    ALUControl => AluControl -- Define operacion a ejecutar por la ALU
  );

  Alu_MIPS : alu
  port map (
    OpA     => Reg1_IDEX,
    OpB     => Alu_Op2,
    Control => AluControl,
    Result  => Alu_Res,
    Zflag   => ALU_IGUAL
  );

  Alu_Op2    <= Reg2_IDEX when ALUSrc_IDEX = '0' else Inmediate_IDEX;
  reg_RD     <= Instruction_IDEX(20 downto 16) when RegDst_IDEX = '0' else Instruction_IDEX(15 downto 11);

  DAddr      <= Alu_result_EXMEM;
  DDataOut   <= Reg2_EXMEM;
  DWrEn      <= MemWrite_EXMEM;
  dRdEn      <= MemRead_EXMEM;
  dataIn_Mem <= DDataIn;

  reg_RD_data <= Mem_data_MEMWB when MemToReg_MEMWB = '1' else Alu_result_MEMWB;

end architecture;
