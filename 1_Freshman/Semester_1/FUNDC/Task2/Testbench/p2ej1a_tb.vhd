----------------------------------------------------------------------
-- Fichero: P2EJ1a_tb.vhd
-- Descripcin: Testbench para el ejercicio 1a de la prctica 2
-- Prctica: 2 -- Ejercicio: 1a
----------------------------------------------------------------------

-- Declaracin de bibliotecas. 
library ieee;
use ieee.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.all;

-- Declaracin de la entidad del testbench (nombre del archivo de simulacin)
entity P2EJ1a_tb is
end P2EJ1a_tb;


architecture behavioral of P2EJ1a_tb is

	component P2EJ1a  			-- Nombre del archivo a simular.  
	PORT( 
		A : in std_logic; 
		B : in std_logic; 
		C : in std_logic; 
		D : in std_logic; 
		Z : out std_logic
	);
   end component;

-- Definicin de las seales auxiliares en las que se van a generan los valores de la simulacin							
   signal a : std_logic;
   signal b : std_logic;
   signal c : std_logic;
   signal d : std_logic;
	signal z : std_logic;
	signal Entrada : std_logic_vector(3 downto 0);
	
-- Se define la constante INSTANTE. Su valor es indiferente, mientras sea mayor que 0. 
-- Sirve para "dejar tiempo" a que el componente a probar (el esquemtico realizado) establezca su salida.
	constant INSTANTE : time := 10 ns;

begin
-- Instancia el componente a probar. Se trata de asociar las seales auxiliares con las seales del archivo a simular (Unit Under Test, uut).
   uut: P2EJ1a port map(
		A => a,
		B => b, 
		C => c, 
		D => d, 
		Z => z 
	);
	
-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la protoboard) y se comprobar su salida (equivalente a ver si los 
-- leds de la protoboard se encienden o no).
	prueba : process
	begin
		for i in 0 to 15			-- genera las 16 combinaciones posibles para los 4 bits de entrada. 
		loop
			Entrada <= conv_std_logic_vector(i,4);
			wait for INSTANTE;
		end loop;
		wait; -- Evita que se repita la simulacin continuamente
	end process prueba;
	
	a <= Entrada(3);
	b <= Entrada(2);
	c <= Entrada(1);
	d <= Entrada(0);

end;