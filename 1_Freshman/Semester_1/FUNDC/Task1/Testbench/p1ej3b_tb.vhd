----------------------------------------------------------------------
-- Fichero: P1EJ3b_tb.vhd
-- Descripción: Testbench para el ejercicio 3b de la práctica 1
-- Práctica: 1 -- Ejercicio: 3b
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;
ENTITY P1EJ3b_tb IS
END P1EJ3b_tb;
ARCHITECTURE behavioral OF P1EJ3b_tb IS 

   COMPONENT P1EJ3b
   PORT( A	:	IN	STD_LOGIC; 
          B	:	IN	STD_LOGIC; 
          C	:	IN	STD_LOGIC; 
          Z	:	OUT	STD_LOGIC);
   END COMPONENT;

   SIGNAL A	:	STD_LOGIC;
   SIGNAL B	:	STD_LOGIC;
   SIGNAL C	:	STD_LOGIC;
   SIGNAL Z	:	STD_LOGIC;
	
	signal entrada : std_logic_vector (2 downto 0);
	constant instante: time := 10 ns;

BEGIN

   UUT: P1EJ3b PORT MAP(
		A => A, 
		B => B, 
		C => C, 
		Z => Z
   );
	
	A <= entrada(2);
	B <= entrada(1);
	C <= entrada(0);


   tb : PROCESS
   BEGIN
		for i in 0 to 7 loop
			entrada <= std_logic_vector (to_unsigned(i,3));
			wait for instante;
		
		end loop;
				
      WAIT; -- will wait forever

   END PROCESS;

-- *** End Test Bench - User Defined Section ***

END;
