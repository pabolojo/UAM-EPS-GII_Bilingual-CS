library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity UnidadControl is
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
end UnidadControl;

architecture behave of UnidadControl is

signal aux: std_logic_vector(2 downto 0);
begin
	with OPCode select
MemToReg <='0' when "000000", -- R-TYPE
		   '0' when "000010", --j
		   '0' when "000100", --beq
		   '0' when "001000", --addi
		   '0' when "001100", --andi
		   '0' when "001101", --ori
		   '1' when "100011", --lw
		   '0' when "101011", --sw
		   '0' when "001010", --slti
		   '0' when others;
		   
	with OPCode select
MemWrite<= '1' when "101011", --sw
		   '0' when others;
		   
	with OPCode select
Branch<='0' when "000000", -- R-TYPE
		   '0' when "000010", --j
		   '1' when "000100", --beq
		   '0' when "001000", --addi
		   '0' when "001100", --andi
		   '0' when "001101", --ori
		   '0' when "100011", --lw
		   '0' when "101011", --sw
		   '0' when "001010", --slti
		   '0' when others;
		 

with Funct select		
aux<= "000" when "100100",
	  "010" when "100000",
      "110" when "100010",
      "101" when "100111",
      "001" when "100101",
      "111" when "101010",
	  "000" when others;

 
	with OPCode select
ALUControl<=aux when "000000", -- R-TYPE
		   "000" when "000010", --j
		   "110" when "000100", --beq
		   "010" when "001000", --addi
		   "000" when "001100", --andi
		   "001" when "001101", --ori
		   "010" when "100011", --lw
		   "010" when "101011", --sw
		   "111" when "001010", --slti
		   "000" when others;
		   
	with OPCode select
ALUSrc<= '0' when "000000", -- R-TYPE
		   '1' when "000010", --j
		   '0' when "000100", --beq
		   '1' when "001000", --addi
		   '1' when "001100", --andi
		   '1' when "001101", --ori
		   '1' when "100011", --lw
		   '1' when "101011", --sw
		   '1' when "001010", --slti
		   '0' when others;
		   
		   with OPCode select
RegDest<='1' when "000000", -- R-TYPE
		   '0' when "000010", --j
		   '0' when "000100", --beq
		   '0' when "001000", --addi
		   '0' when "001100", --andi
		   '0' when "001101", --ori
		   '0' when "100011", --lw
		   '0' when "101011", --sw
		   '0' when "001010", --slti
		   '0' when others;
		   
		   with OPCode select
RegWrite<='1' when "000000", -- R-TYPE
		   '0' when "000010", --j
		   '0' when "000100", --beq
		   '1' when "001000", --addi
		   '1' when "001100", --andi
		   '1' when "001101", --ori
		   '1' when "100011", --lw
		   '0' when "101011", --sw
		   '1' when "001010", --slti
		   '0' when others;
		  
		  	with OPCode select
ExtCero<='0' when "000000", -- R-TYPE
		   '0' when "000010", --j
		   '0' when "000100", --beq
		   '0' when "001000", --addi
		   '1' when "001100", --andi
		   '1' when "001101", --ori
		   '0' when "100011", --lw
		   '0' when "101011", --sw
		   '0' when "001010", --slti
		   '0' when others;
		   
		   with OPCode select
Jump<='0' when "000000", -- R-TYPE
		   '1' when "000010", --j
		   '0' when "000100", --beq
		   '0' when "001000", --addi
		   '0' when "001100", --andi
		   '0' when "001101", --ori
		   '0' when "100011", --lw
		   '0' when "101011", --sw
		   '0' when "001010", --slti
		   '0' when others;
end behave;