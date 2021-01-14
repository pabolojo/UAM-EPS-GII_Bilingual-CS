----------------------------------------------------------------------
-- File: MicroSuma.vhd
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

entity MicroSuma is
	port (
		Clk : in std_logic; -- Clock
		NRst : in std_logic; -- Reset active low level
		MemProgAddr : out std_logic_vector(31 downto 0); -- Address for the program memory
		MemProgData : in std_logic_vector(31 downto 0) -- Operation code
	);
	end MicroSuma;

architecture Practica of MicroSuma is

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

	-- Declaration of auxiliary signal
signal op1aux:std_logic_vector (31 downto 0);
signal resaux:std_logic_vector (31 downto 0);
signal op2sign:std_logic_vector (31 downto 0);
signal procc:std_logic_vector (31 downto 0);
signal inmdataext:std_logic_vector (31 downto 16);
signal instruction:std_logic_vector (31 downto 0);

begin


	instruction<=MemProgData;
	
	-- Instantiation of RegMIPS
	
	registermap: RegsMIPS port map (
	Clk=>Clk,
	NRst=>NRst,
	A1=>instruction(25 downto 21),
	Rd1=>op1aux,
	A2=>conv_std_logic_vector(0,5),
	Rd2=>open,
	A3=>instruction(20 downto 16),
	Wd3=>resaux,
	We3=>'1');
	
	-- Instantiation of ALUMIPS
	
	alumap: ALUMIPS port map (
	Op1=>op1aux,
	Op2=>op2sign,
	ALUControl=>"010",
	Res=>resaux,
	Z=>open);
	
	-- Sign Extension
	
	inmdataext<=(others=>instruction(15));
	op2sign<=inmdataext & instruction(15 downto 0);
 
	-- PC route

	proccounter: process(Clk,NRst)
	  begin
		 if NRst='0' then
			procc<=(others=>'0');
		 elsif rising_edge(Clk) then
			procc<=procc+4;
	  end if;
	end process proccounter;
	
	MemProgAddr<=procc;
	
	end Practica;

