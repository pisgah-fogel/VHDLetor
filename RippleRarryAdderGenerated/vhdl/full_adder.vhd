library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity full_adder is
    port (
        i_a  : in std_logic;
        i_b  : in std_logic;
        i_carry : in std_logic;
        o_sum   : out std_logic;
        o_carry : out std_logic
    );
end full_adder;
 
architecture rtl of full_adder is
    signal w_wire_1 : std_logic;
    signal w_wire_2 : std_logic;
    signal w_wire_3 : std_logic;
begin
    w_wire_1 <= i_a xor i_b;
    w_wire_2 <= w_wire_1 and i_carry;
    w_wire_3 <= i_a and i_b;

    o_sum   <= w_wire_1 xor i_carry;
    o_carry <= w_wire_2 or w_wire_3;
end rtl;