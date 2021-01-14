library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_logic_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity Deco3a8Reg is
port (
D : in std_logic_vector (2 downto 0);
CE : in std_logic;
Clk : in std_logic;
Reset : in std_logic;
Q : out std_logic_vector (7 downto 0)
);
end Deco3a8Reg;

architecture decoreg of Deco3a8Reg is
component Deco3a8
port(
Dd : in std_logic_vector (2 downto 0);
S : out std_logic_vector (7 downto 0)
);
end component;
component Registro
    port ( 
		Dr : in  std_logic_vector(7 downto 0);
		Reset : in  std_logic;
		Clk : in  std_logic;
		Ce : in  std_logic;
		Qr : out  std_logic_vector(7 downto 0)
	);
end component;

signal s1: std_logic_vector(7 downto 0);
begin
d1: Deco3a8 port map(Dd=>D, S=>s1);
r1: Registro port map(Dr=>s1,Qr=>Q,Reset=>Reset,Clk=>Clk,Ce=>CE);
end decoreg;