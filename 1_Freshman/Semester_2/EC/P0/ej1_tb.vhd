library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_logic_arith.ALL;
use IEEE.std_logic_unsigned.ALL;
entity P1e1_tb is
end P1e1_tb;
architecture Practica of P1e1_tb is
component P1e1
port(
A : in std_logic;
B : in std_logic;
C : in std_logic;
Z : out std_logic
);
end component;
-- Entradas
signal sigA : std_logic := '0';
signal sigB : std_logic := '0';
signal sigC : std_logic := '0';
-- Salidas
signal z : std_logic;
constant ESPERA : time := 10 ns;
begin
uut: P1e1 port map (
A => sigA,
B => sigB,
C => sigC,
Z => z
);
process
begin
sigA <= '0'; sigB <= '0'; sigC <= '0';
wait for ESPERA;
assert z = '0'
report " Error in the case 000"
severity failure;

sigA <= '0'; sigB <= '0'; sigC <= '1';
wait for ESPERA;
assert z = '0'
report " Error in the case 001"
severity failure;

sigA <= '0'; sigB <= '1'; sigC <= '0';
wait for ESPERA;
assert z = '0'
report " Error in the case 010"
severity failure;

sigA <= '0'; sigB <= '1'; sigC <= '1';
wait for ESPERA;
assert z = '1'
report " Error in the case 011"
severity failure;

sigA <= '1'; sigB <= '0'; sigC <= '0';
wait for ESPERA;
assert z = '0'
report " Error in the case 100"
severity failure;

sigA <= '1'; sigB <= '0'; sigC <= '1';
wait for ESPERA;
assert z = '1'
report " Error in the case 101"
severity failure;

sigA <= '1'; sigB <= '1'; sigC <= '0';
wait for ESPERA;
assert z = '0'
report " Error in the case 110"
severity failure;

sigA <= '1'; sigB <= '1'; sigC <= '1';
wait for ESPERA;
assert z = '1'
report " Error in the case 111"
severity failure;

-- Continue with all the remaining cases. There are 7 more cases to be checked!
report " If this message appears, the simulation is correct.";
wait;
end process;
end Practica;