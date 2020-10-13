library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity half_adder_tb is
end half_adder_tb;

architecture behave of half_adder_tb is
    signal r_a  : std_logic := '0';
    signal r_b  : std_logic := '0';
    signal w_sum   : std_logic;
    signal w_carry : std_logic;
begin

    UUT : entity work.half_adder
    port map (
        i_a  => r_a,
        i_b  => r_b,
        o_sum   => w_sum,
        o_carry => w_carry
    );

    process is
    begin
        r_a <= '0';
        r_b <= '0';
        wait for 10 ns;
        r_a <= '0';
        r_b <= '1';
        wait for 10 ns;
        r_a <= '1';
        r_b <= '0';
        wait for 10 ns;
        r_a <= '1';
        r_b <= '1';
        wait for 10 ns;
        wait for 10 ns;
        assert FALSE Report "Simulation Done" severity FAILURE;
    end process;
end behave;