library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_logic_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity P1e1 is port(a:in std_logic; b:in std_logic; c:in std_logic; z:out std_logic);
end P1e1;

architecture circuit of P1e1 is begin 
z<=(a or b) and c;
end circuit;
