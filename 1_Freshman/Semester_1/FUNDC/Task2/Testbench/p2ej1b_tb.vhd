----------------------------------------------------------------------
-- Fichero: P2EJ1b_tb.vhd
-- Descripción: Testbench para el ejercicio 1b de la práctica 2
-- Práctica: 2 -- Ejercicio: 1b
----------------------------------------------------------------------

-- Declaración de bibliotecas. 
library ieee;
use ieee.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.all;

-- Declaración de la entidad del testbench (nombre del archivo de simulación).
entity P2EJ1b_tb is
end P2EJ1b_tb;


architecture behavioral of P2EJ1b_tb is

	component P2EJ1b  			-- Nombre del archivo a simular.  
	PORT( 
		A : in std_logic; 
		B : in std_logic; 
		C : in std_logic; 
		D : in std_logic; 
		Z : out std_logic
	);
   end component;

-- Definición de las señales auxiliares en las que se van a generan los valores de la simulación							
   signal a : std_logic;
   signal b : std_logic;
   signal c : std_logic;
   signal d : std_logic;
	signal z : std_logic;
	signal Entrada : std_logic_vector(3 downto 0);
	
-- Se define la constante INSTANTE. Su valor es indiferente, mientras sea mayor que 0. 
-- Sirve para "dejar tiempo" a que el componente a probar (el esquemático realizado) establezca su salida.
	constant INSTANTE : time := 10 ns;

begin
-- Instancia el componente a probar. Se trata de asociar las señales auxiliares con las señales del archivo a simular (Unit Under Test, uut).
   uut: P2EJ1b port map(
		A => a,
		B => b, 
		C => c, 
		D => d, 
		Z => z 
	);
	
-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la protoboard) y se comprobará su salida (equivalente a ver si los 
-- leds de la protoboard se encienden o no).
	prueba : process
	begin
		for i in 0 to 15			-- genera las 16 combinaciones posibles para los 4 bits de entrada. 
		loop
			Entrada <= conv_std_logic_vector(i,4);
			wait for INSTANTE;
		end loop;
		wait; -- Evita que se repita la simulación continuamente
	end process prueba;
	
	a <= Entrada(3);
	b <= Entrada(2);
	c <= Entrada(1);
	d <= Entrada(0);

end;