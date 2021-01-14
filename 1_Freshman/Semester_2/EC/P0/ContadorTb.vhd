library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_LOGIC_arith.ALL;
use IEEE.std_logic_unsigned.ALL;

entity ContadorTb is
end entity;

architecture Simulacion of ContadorTb is
component Contador
    Port (
		Clk : in  STD_LOGIC;
		Reset : in  STD_LOGIC;
		Ce : in  STD_LOGIC;
		Up : in  STD_LOGIC;
		Q : out  STD_LOGIC_VECTOR (7 downto 0)
	);
end component;

	signal q : std_logic_vector(7 downto 0);
	signal ce : std_logic := '0';
	signal clk : std_logic := '0';
	signal reset : std_logic := '0';
	signal up : std_logic := '0';
	
constant CLKPERIOD : time := 10 ns;
	constant ESPERA : time := 1 ns;
	
	begin
	
	uut: Contador port map (
		Clk => clk,
		Ce => ce,
		Up => up,
		Reset => reset,
		Q => q
	);

	-- Clock generator process
	CLKPROCESS :process
	begin
		clk <= '0';
		wait for CLKPERIOD/2;
		clk <= '1';
		wait for CLKPERIOD/2;
	end process;

	-- Stimulation process
	stim_proc: process
	begin
		-- Initialization
		up <= '0';
		ce <= '1';
		reset <= '1';

		wait for ESPERA;
		Assert q = "00000000" 
			report "Reset error"
			severity failure;

		-- Chip enable connected
		reset <= '0';
		ce <= '1';
		up <= '1';

		for i in 1 to 255 loop
			wait until clk = '1';
			wait for ESPERA;
			assert conv_integer(q)=(i)
				report "Error with value i = "  & integer'image(i)
				severity failure;
		end loop;
		
		wait until clk='1';
		wait for ESPERA;
		assert conv_integer(q)=(0)
			report "Error overflowing"
			severity failure;
		-- Chip enable down
		ce <= '1';
		up <= '0';

		for i in 255 downto 1 loop
			wait until clk = '1';
			wait for ESPERA;
			assert conv_integer(q)=(i)
				report "Error with value i = "  & integer'image(i)
				severity failure;
		end loop;

		report "If this message appears, the simulation is correct";
		wait;
	end process;
end Simulacion;