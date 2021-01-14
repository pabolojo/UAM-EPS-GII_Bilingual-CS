library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_logic_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity Deco3a8 is
port (
Dd : in std_logic_vector (2 downto 0);
S : out std_logic_vector (7 downto 0)
);
end Deco3a8;

architecture deco of Deco3a8 is
begin
with Dd select
S<="00000001" when "000",
"00000010" when "001",
"00000100" when "010",
"00001000" when "011",
"00010000" when "100",
"00100000" when "101",
"01000000" when "110",
"10000000" when others;
end deco;