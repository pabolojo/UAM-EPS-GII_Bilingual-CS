---------------------------------------------------------------------------------
-- File: Registro.vhd
-- Description: 1 bit register with Chip Enable
-- Last modification date: 2019-01-23

-- Authors: Sofia Martnez (2019), Alberto Snchez (2012), Fernando Lpez (2010) 
-- Subject: C.E. 1 grade
-- Laboratory group:
-- Theory group:
-- Task: 1
-- Exercise: 2
---------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;


--Entity definition
--The register has a data input (D), a Reset input, CLK and CE
-- And one bit output (Q)
entity Registro is
    port ( 
		Dr : in  std_logic_vector(7 downto 0);
		Reset : in  std_logic;
		Clk : in  std_logic;
		Ce : in  std_logic;
		Qr : out  std_logic_vector(7 downto 0)
	);
end Registro;

architecture Practica of Registro is
	
begin

	--The register is sensitive to Reset (asynchronous) and to the clock signal
	process (Reset, Clk)
	begin
		-- If the reset is active the output is 0
		-- If there is a rising edge clock
		if rising_edge (Clk) then
			if Reset = '1' then
			Qr <= "00000000";
			-- If the chip enable is active
			elsif Ce = '1' then
				Qr <= Dr;
			end if;
		end if;
	end process;

end Practica;
