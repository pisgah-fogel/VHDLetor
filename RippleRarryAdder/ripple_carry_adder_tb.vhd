library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity full_adder_tb is
end full_adder_tb;

architecture behave of full_adder_tb is
    signal r_a  : std_logic := '0';
    signal r_b  : std_logic := '0';
    signal w_sum   : std_logic;
    signal r_carry : std_logic := '0';
    signal w_carry : std_logic;
begin

    UUT : entity work.full_adder
    port map (
        i_a  => r_a,
        i_b  => r_b,
        i_carry => r_carry,
        o_sum   => w_sum,
        o_carry => w_carry
    );

    process is
    begin
        r_a <= '0';
        r_b <= '0';
        r_carry <= '0';
        wait for 10 ns;
        r_a <= '0';
        r_b <= '1';
        r_carry <= '0';
        wait for 10 ns;
        r_a <= '1';
        r_b <= '0';
        r_carry <= '0';
        wait for 10 ns;
        r_a <= '1';
        r_b <= '1';
        r_carry <= '0';
        wait for 10 ns;
        r_a <= '0';
        r_b <= '0';
        r_carry <= '1';
        wait for 10 ns;
        r_a <= '0';
        r_b <= '1';
        r_carry <= '1';
        wait for 10 ns;
        r_a <= '1';
        r_b <= '0';
        r_carry <= '1';
        wait for 10 ns;
        r_a <= '1';
        r_b <= '1';
        r_carry <= '1';
        wait for 10 ns;
        wait for 10 ns;
        assert FALSE Report "Simulation Done" severity FAILURE;
    end process;
end behave;