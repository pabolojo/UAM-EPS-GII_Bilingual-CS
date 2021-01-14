----------------------------------------------------------------------
-- File: MicroMIPS.vhd
-- Description: Simplified Micro MIPS, only addition with immediate data
-- Date last modification: 2019-02-22
-- Authors: 
-- Sbuject: Sbuject: C.E. 1st grade
-- Laboratory group:
-- Theory group:
-- Task: 2
-- Exercise: 3
----------------------------------------------------------------------



library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity MicroMIPS is
	port (
		Clk : in std_logic; -- Reloj
		NRst : in std_logic; -- Low level active Reset 
		MemProgData : in std_logic_vector(31 downto 0); -- Operation code
		MemDataDataRead : in std_logic_vector(31 downto 0);
		MemProgAddr : out std_logic_vector(31 downto 0); -- Address for the program memory
		MemDataWe : out std_logic;
		MemDataAddr :  out std_logic_vector(31 downto 0);
		MemDataDataWrite : out std_logic_vector(31 downto 0)
	);
end MicroMIPS;

architecture Practica of MicroMIPS is

	-- Declaration of RegsMIPS
component RegsMIPS
	port (
		Clk : in std_logic; -- Clock
		NRst : in std_logic; -- Asynchronous Reset in low level
		A1 : in std_logic_vector(4 downto 0); -- Address for the port Rd1
		Rd1 : out std_logic_vector(31 downto 0); -- Data of the port Rd1
		A2 : in std_logic_vector(4 downto 0); -- Address for the port Rd2
		Rd2 : out std_logic_vector(31 downto 0); -- Dataof the port Rd2
		A3 : in std_logic_vector(4 downto 0); -- Address for the port Wd3
		Wd3 : in std_logic_vector(31 downto 0); -- Input data Wd3
		We3 : in std_logic -- Enable of the register bank
	); 
end component;
	-- Declaration of ALUMIPS
component ALUMIPS
	Port (
		Op1 : in std_logic_vector (31 downto 0);
		Op2 : in std_logic_vector (31 downto 0);
		ALUControl : in std_logic_vector (2 downto 0);
		Res : out std_logic_vector (31 downto 0);
		Z : out std_logic
		);
end component;
	--Declaration of Multiplexer
component Mux 
	port(d0,d1 : in std_logic_vector(31 downto 0);
		s : in std_logic;
		y : out std_logic_vector(31 downto 0));
end component;

component Mux2
	port(d0,d1 : in std_logic_vector(4 downto 0);
		s : in std_logic;
		y : out std_logic_vector(4 downto 0)
		);
end component;

	--Declaration of Control Unit
component UnidadControl
	port (
		OPCode : in std_logic_vector(5 downto 0);
		Funct : in std_logic_vector(5 downto 0);
		MemToReg : out std_logic;
		MemWrite : out std_logic;
		Branch : out std_logic;
		ALUControl : out std_logic_vector(2 downto 0);
		ALUSrc : out std_logic;
		RegDest : out std_logic;
		RegWrite : out std_logic;
		ExtCero : out std_logic;
		Jump : out std_logic
	);
end component;

		
	-- Declaration of auxiliary signal
signal aux1reg, extend_signo,extend_zero, auxCounter,auxCounter2, aux_shift1, aux_add,aux_shift_extra, aux_ALU, auxMemData,auxCounter_mas4, aux_rd2: std_logic_vector(31 downto 0);
signal aux_mult_in1, aux_mult_inn1,aux_mult_out1, aux_mult_out5 : std_logic_vector(31 downto 0);
signal aux_mult_out2 : std_logic_vector(4 downto 0);
signal aux_mult_out3 : std_logic_vector(31 downto 0);
signal MemToReg,MemWrite,Branch,ALUSrc,RegDest,RegWrite,ExtCero,Jump , zero,PCSrc  : std_logic;
signal ALUControl : std_logic_vector(2 downto 0);
begin

	-- Instantiation of RegMIPS
Reg: RegsMIPS port map(Clk=>Clk, NRst=>NRst,A1=>MemProgData(25 downto 21), Rd1=>aux1reg, A2=>MemProgData(20 downto 16), Rd2=>aux_rd2, A3=>aux_mult_out2, Wd3=>aux_mult_out3, We3=>RegWrite  );
aux_mult_in1<=aux_rd2;
	-- Instantiation of UnidadControl
Control_unit: 	UnidadControl port map(OPCode=>MemProgData(31 downto 26),Funct=>MemProgData(5 downto 0),MemToReg=>MemToReg,MemWrite=>MemDataWE,Branch=>Branch,ALUControl=>ALUControl,ALUSrc=>ALUSrc,RegDest=>RegDest,RegWrite=>RegWrite,ExtCero=>ExtCero,Jump=>Jump );
    -- Multiplexers 
Mux1: Mux port map(d0=>aux_mult_in1,d1=>aux_mult_inn1, s=>ALUSrc ,y=>aux_mult_out1);

Mux_extra: Mux2 port map(d0=>MemProgData(20 downto 16),d1=>MemProgData(15 downto 11), s=>RegDest ,y=>aux_mult_out2);

Mux3: Mux port map(d0=>aux_ALU,d1=>MemDataDataRead, s=>MemToReg ,y=>aux_mult_out3);

Mux4: Mux port map(d0=>extend_signo,d1=>extend_zero, s=>ExtCero ,y=>aux_mult_inn1);

Mux5: Mux port map(d0=>auxCounter_mas4,d1=>aux_add, s=>PCSrc ,y=>aux_mult_out5);

Mux6: Mux port map(d0=>aux_mult_out5,d1=>aux_shift_extra, s=>Jump ,y=>auxCounter2);

	-- Instantiation of ALUMIPS
ALU: ALUMIPS port map(Op1=>aux1reg, Op2=>aux_mult_out1, ALUControl=>ALUControl , Res=>aux_ALU, Z=>zero);	
MemDataAddr<=aux_ALU;
	-- Sign Extension
extend_signo<=x"0000" & MemProgData(15 downto 0) when MemProgData(15)='0' else
		x"FFFF" & MemProgData(15 downto 0);
extend_zero<=x"0000" & MemProgData(15 downto 0);

	--Shifters
aux_shift1<=extend_signo(29 downto 0) & "00";

aux_shift_extra<=auxCounter_mas4(31 downto 28) & MemProgData(25 downto 0) & "00";

	-- Branching
PCSrc<=zero and Branch;
aux_add<= auxCounter_mas4 + aux_shift1;	


--<=MemWrite;
MemDataDataWrite<=aux_rd2;
		-- PC route
	process(Clk,NRst)
	begin
		if NRst='0' then
		 auxCounter<=x"00000000";
		-- auxCounter2<=x"00000000";
		elsif rising_edge(Clk) then
		 auxCounter<=auxCounter2;	
		end if;
	end process;	

	
auxCounter_mas4<=auxCounter+4;
MemProgAddr<=auxCounter;
end Practica;