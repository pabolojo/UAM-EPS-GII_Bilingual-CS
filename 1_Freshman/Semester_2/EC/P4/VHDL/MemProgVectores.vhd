

----------------------------------------------------------------------
-- File: MemProgPlantilla.vhd
-- Description: Template for the prorammemory MIPS
-- Date last modification: 2019-03-29

-- Authors: Sofía Martínez (2019), Alberto Sánchez (2012-2018), Ángel de Castro (2010-2015)
-- Sbuject: Sbuject: C.E. 1st grade
-- Laboratory group:
-- Theory group:
-- Task: 4
-- Exercise: 3
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity MemProgVectores is
	port (
		MemProgAddr : in std_logic_vector(31 downto 0); -- Address of the program memory
		MemProgData : out std_logic_vector(31 downto 0) -- Operation code
	);
end MemProgVectores;

architecture Simple of MemProgVectores is

begin

	LecturaMemProg: process(MemProgAddr)
	begin
		-- The memory gives back a value for each address.
		-- These values are the program codes for each instruction,
		-- which are located in its address.
		case MemProgAddr is
		-------------------------------------------------------------
		-- Only introduce changes from here!!		
		when X"00000000"=>MemProgData<=X"8c102000";
		when X"00000004"=>MemProgData<=X"02108820";
		when X"00000008"=>MemProgData<=X"02318020";
		when X"0000000C"=>MemProgData<=X"20080000";
		when X"00000010"=>MemProgData<=X"11100008";
		when X"00000014"=>MemProgData<=X"8d0a2004";
		when X"00000018"=>MemProgData<=X"8d09201c";
		when X"0000001C"=>MemProgData<=X"01296020";
		when X"00000020"=>MemProgData<=X"018c4820";
		when X"00000024"=>MemProgData<=X"012a5820";
		when X"00000028"=>MemProgData<=X"ad0b2034";
		when X"0000002C"=>MemProgData<=X"21080004";
		when X"00000030"=>MemProgData<=X"08000004";
		when X"00000034"=>MemProgData<=X"0800000d";
			-- For each instruction in.text, we add a line as:
			-- when DIRECCION => MemProgData <= INSTRUCCION;
			-- For example, of the position 0x00000000 shuld be save the instruction with machine code 0x20010004, it is:
			--when X"00000000" => MemProgData <= X"20010004";
		-- Until here!	
		---------------------------------------------------------------------	
			
			when others => MemProgData <= X"00000000"; -- Rest of empty memory
		end case;
	end process LecturaMemProg;

end Simple;

