library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity ripple_carry_adder is
    generic (
    g_WIDTH : natural := 2
    );
    port (
        i_add_term1  : in std_logic_vector(g_WIDTH-1 downto 0);
        i_add_term2  : in std_logic_vector(g_WIDTH-1 downto 0);
        o_result   : out std_logic_vector(g_WIDTH downto 0)
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

    signal w_carry : std_logic_vector(g_WIDTH downto 0);
    signal w_sum   : std_logic_vector(g_WIDTH-1 downto 0);
begin
    w_carry(0) <= '0';

    SET_WIDTH : for ii in 0 to g_WIDTH-1 generate
    i_FULL_ADDER_INST : full_adder
      port map (
        i_a  => i_add_term1(ii),
        i_b  => i_add_term2(ii),
        i_carry => w_carry(ii),
        o_sum   => w_sum(ii),
        o_carry => w_carry(ii+1)
        );
  end generate SET_WIDTH;
 
  o_result <= w_carry(g_WIDTH) & w_sum;
end rtl;