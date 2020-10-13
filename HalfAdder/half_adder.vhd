library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity half_adder is
    port (
    i_a  : in std_logic;
    i_b  : in std_logic;
    o_sum   : out std_logic;
    o_carry : out std_logic
    );
end half_adder;
 
architecture rtl of half_adder is
begin
    o_sum   <= i_a xor i_b;
    o_carry <= i_a and i_b;
end rtl;