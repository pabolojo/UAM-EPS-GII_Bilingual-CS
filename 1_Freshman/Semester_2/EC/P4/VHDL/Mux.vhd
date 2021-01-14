library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity Mux is
	port(d0,d1 : in std_logic_vector(31 downto 0);
		s : in std_logic;
		y : out std_logic_vector(31 downto 0)
		);
end Mux;
architecture behav of Mux is
begin
y <= d0 when s = '0' else d1;
end behav;