---------------------------------------------------------------------------------
-- File: Contador.vhd
-- Description: 8 bits counter with Chip Enable and account direction selector 
-- Last modification date: 2019-01-23

-- Authors: Sofia Martínez (2019), Alberto Sánchez (2012), Fernando López (2010) 
-- Subject: C.E. 1º grade
-- Laboratory group:
-- Theory group:
-- Task: 1
-- Exercise: 3
---------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

-- 8 bits counter
entity Contador is
    Port (
		Clk : in  STD_LOGIC;
		Reset : in  STD_LOGIC;
		Ce : in  STD_LOGIC;
		Up : in  STD_LOGIC;
		Q : out  STD_LOGIC_VECTOR (7 downto 0)
	);
end Contador;

architecture Practica of Contador is

	-- Auxiliary signal to save the value
	signal qTemp : std_logic_vector (7 downto 0);

	begin

	Q <= qTemp;

	process (Clk, Reset)
	begin
		if Reset = '1' then
			qTemp <= (OTHERS => '0');
		elsif rising_edge(Clk) then
			if Ce = '1' then
				if Up = '1' then
					qTemp <= qTemp + 1;
				else
					qTemp <= qTemp - 1;
				end if;
			end if;
		end if;

	end process;

end Practica;
