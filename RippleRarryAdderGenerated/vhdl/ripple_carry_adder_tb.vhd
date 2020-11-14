library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ripple_carry_adder_tb is
end ripple_carry_adder_tb;

architecture behave of ripple_carry_adder_tb is
    constant c_WIDTH : integer := 4;

    signal r_ADD_1  : std_logic_vector(c_WIDTH-1 downto 0) := (others => '0');
    signal r_ADD_2  : std_logic_vector(c_WIDTH-1 downto 0) := (others => '0');
    signal w_RESULT : std_logic_vector(c_WIDTH downto 0);

    component ripple_carry_adder is
        generic (
            g_WIDTH : natural
        );
        port (
            i_add_term1 : in  std_logic_vector(g_WIDTH-1 downto 0);
            i_add_term2 : in  std_logic_vector(g_WIDTH-1 downto 0);
            o_result    : out std_logic_vector(g_WIDTH downto 0)
        );
    end component ripple_carry_adder;

begin

    UUT : ripple_carry_adder
    generic map (
      g_WIDTH     => c_WIDTH
    )
    port map (
      i_add_term1 => r_ADD_1,
      i_add_term2 => r_ADD_2,
      o_result    => w_RESULT
      );
   
  process is
  begin
    r_ADD_1 <= "0000";
    r_ADD_2 <= "0100";
    wait for 10 ns;
    r_ADD_1 <= "1000";
    r_ADD_2 <= "0100";
    wait for 10 ns;
    r_ADD_1 <= "0100";
    r_ADD_2 <= "1100";
    wait for 10 ns;
    r_ADD_1 <= "1100";
    r_ADD_2 <= "1100";
    wait for 10 ns;
    wait for 10 ns;
    assert FALSE Report "Simulation Done" severity FAILURE;
  end process;
end behave;