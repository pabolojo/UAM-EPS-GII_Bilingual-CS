library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity Mux2 is
	port(d0,d1 : in std_logic_vector(4 downto 0);
		s : in std_logic;
		y : out std_logic_vector(4 downto 0)
		);
end Mux2;
architecture behav of Mux2 is
begin
y <= d0 when s = '0' else d1;
end behav;