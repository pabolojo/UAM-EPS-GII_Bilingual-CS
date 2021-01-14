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
signal Resaux:std_logic_vector (31 downto 0);

begin
Res<=Resaux;
process(ALUControl,Resaux)
begin

if ALUControl="000" then
  Resaux <= Op1 and Op2;
elsif ALUControl="001" then
  Resaux <= Op1 or Op2;
elsif ALUControl="010" then
  Resaux <= Op1 + Op2;
elsif ALUControl="101" then
  Resaux <= Op1 nor Op2;
elsif ALUControl="110" then
  Resaux <= Op1 - Op2;
elsif ALUControl="111" then
  if Op1<Op2 then
    Resaux<=(31 downto 1 => '0',0=>'1');
  else
    Resaux<=(others=>'0');
  end if;
end if;

if Resaux=conv_std_logic_vector(0,32) then
  Z<='1';
else
  Z<='0';
end if;

end process;
end Practica;
