----------------------------------------------------------------------
-- File: ALUMIPS.vhd
-- Description: ALU of the microprocessor MIPS
-- Date last modification: 

-- Authors: 
-- Sbuject: Sbuject: C.E. 1st grade
-- Laboratory group:
-- Theory group:
-- Task: 2
-- Exercise: 2
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_signed.ALL;

entity ALUMIPS is
	Port (
		Op1 : in std_logic_vector (31 downto 0);
		Op2 : in std_logic_vector (31 downto 0);
		ALUControl : in std_logic_vector (2 downto 0);
		Res : out std_logic_vector (31 downto 0);
		Z : out std_logic
		);
end ALUMIPS;

architecture Practica of ALUMIPS is

signal aux1, aux2, auxxx: std_logic_vector(31 downto 0);
signal number : std_logic_vector(31 downto 0);
begin
 aux1<=Op1-Op2;
 aux2<=aux1  when ((Op1(31)='0' and Op2(31)='0') or (Op1(31)='1' and Op2(31)='1')) else 
		Op2	when ((Op1(31)='1' and Op2(31)='0')) else
		Op1;
 
 number<= (others=>'0') when aux2(31)='0' else
			x"00000001";
 
 with ALUControl select
 auxxx<= Op1 and Op2 when "000",
     Op1 or Op2 when "001",
	 Op1 + Op2 when "010",
	 Op1 nor Op2 when "101",
	 aux1 when "110",
	 number when "111",
	 (others=>'0') when others;
	 
 Z<= '1' when conv_integer(auxxx) /=0 else
     '0';
Res<=auxxx;

end Practica;
