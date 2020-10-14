library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity ripple_carry_adder is
    port (
        i_add_term1  : in std_logic_vector(1 downto 0);
        i_add_term2  : in std_logic_vector(1 downto 0);
        o_result   : out std_logic_vector(2 downto 0)
    );
end ripple_carry_adder;
 
architecture rtl of ripple_carry_adder is
    component full_adder is
        port (
            i_a     : in  std_logic;
            i_b     : in  std_logic;
            i_carry : in  std_logic;
            o_sum   : out std_logic;
            o_carry : out std_logic
        );
    end component full_adder;

    signal w_carry : std_logic_vector(2 downto 0);
    signal w_sum   : std_logic_vector(1 downto 0);
begin
    w_carry(0) <= '0';

    FULL_ADDER_1_INST : full_adder
        port map (
            i_a  => i_add_term1(0),
            i_b  => i_add_term2(0),
            i_carry => w_carry(0),
            o_sum   => w_sum(0),
            o_carry => w_carry(1)
        );

    FULL_ADDER_2_INST : full_adder
        port map (
            i_a  => i_add_term1(1),
            i_b  => i_add_term2(1),
            i_carry => w_carry(1),
            o_sum   => w_sum(1),
            o_carry => w_carry(2)
        );

    o_result <= w_carry(2) & w_sum;
end rtl;