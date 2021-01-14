---------------------------------------------------------------------------------
-- File: Deco2a4.vhd
-- Description: Decoder 2 to 4
-- Last modification date: 2019-01-23

-- Authors: Sofia Martínez (2019), Alberto Sánchez (2012), Fernando López (2010) 
-- Subject: C.E. 1º grade
-- Laboratory group:
-- Theory group:
-- Task: 1
-- Exercise: 2
---------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;


entity Deco2a4 is
    port ( 
		D : in  std_logic_vector (1 downto 0);
		Q : out  std_logic_vector (3 downto 0)
	);
end Deco2a4;

architecture Practica of Deco2a4 is

begin

	process (D)
	begin
		case D is
			when "00" => Q <= "0001";
			when "01" => Q <= "0010";
			when "10" => Q <= "0100";
			when others => Q <= "1000";
		end case;
	end process;

end Practica;
