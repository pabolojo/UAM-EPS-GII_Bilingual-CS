--------------------------------------------------------------------------------
-- Copyright (c) 1995-2003 Xilinx, Inc.
-- All Right Reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : ISE
--  /   /         Filename : p4ej1_tb.vhw
-- /___/   /\     Timestamp : Wed Nov 01 10:10:36 2017
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: 
--Design Name: p4ej1_tb
--Device: Xilinx
--

library UNISIM;
use UNISIM.Vcomponents.ALL;
library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
USE IEEE.STD_LOGIC_TEXTIO.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE STD.TEXTIO.ALL;

ENTITY p4ej1_tb IS
END p4ej1_tb;

ARCHITECTURE testbench_arch OF p4ej1_tb IS
    COMPONENT p4ej1
        PORT (
            CLK : In std_logic;
            CLR : In std_logic;
            S0 : In std_logic;
            S1 : In std_logic;
            AD : Out std_logic;
            AI : Out std_logic;
            RD : Out std_logic;
            RI : Out std_logic;
            VD : Out std_logic;
            VI : Out std_logic
        );
    END COMPONENT;

    SIGNAL CLK : std_logic := '0';
    SIGNAL CLR : std_logic := '0';
    SIGNAL S0 : std_logic := '0';
    SIGNAL S1 : std_logic := '0';
    SIGNAL AD : std_logic := '0';
    SIGNAL AI : std_logic := '0';
    SIGNAL RD : std_logic := '0';
    SIGNAL RI : std_logic := '0';
    SIGNAL VD : std_logic := '0';
    SIGNAL VI : std_logic := '0';

    constant PERIOD : time := 200 ns;
    constant DUTY_CYCLE : real := 0.5;
    constant OFFSET : time := 100 ns;

    BEGIN
        UUT : p4ej1
        PORT MAP (
            CLK => CLK,
            CLR => CLR,
            S0 => S0,
            S1 => S1,
            AD => AD,
            AI => AI,
            RD => RD,
            RI => RI,
            VD => VD,
            VI => VI
        );

        PROCESS    -- clock process for CLK
        BEGIN
            WAIT for OFFSET;
            CLOCK_LOOP : LOOP
                CLK <= '0';
                WAIT FOR (PERIOD - (PERIOD * DUTY_CYCLE));
                CLK <= '1';
                WAIT FOR (PERIOD * DUTY_CYCLE);
            END LOOP CLOCK_LOOP;
        END PROCESS;

        PROCESS
             BEGIN
                -- -------------  Current Time:  200ns
                CLR <= '1';
					 WAIT FOR 100 ns;
					 CLR <= '0';
					 WAIT FOR 100 ns;
                -- -------------------------------------
					 -- -------------  Current Time:  785ns
                WAIT FOR 585 ns;
                S0 <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  1185ns
                WAIT FOR 400 ns;
                S0 <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  2185ns
                WAIT FOR 1000 ns;
                S1 <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  2585ns
                WAIT FOR 400 ns;
                S1 <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  3185ns
                WAIT FOR 600 ns;
                S0 <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  4185ns
                WAIT FOR 1000 ns;
                S1 <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  7385ns
                WAIT FOR 3200 ns;
                S0 <= '0';
                S1 <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  8385ns
                WAIT FOR 1000 ns;
                S1 <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  8585ns
                WAIT FOR 200 ns;
                S1 <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  8985ns
                WAIT FOR 400 ns;
                S0 <= '1';
                -- -------------------------------------
                WAIT FOR 1415 ns;


            END PROCESS;

    END testbench_arch;

