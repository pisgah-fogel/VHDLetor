module full_adder
(
    input wire i_bit1,
    input wire i_bit2,
    input wire i_carry,
    output wire o_sum,
    output wire o_carry
    );

    wire   w_WIRE_1;
    wire   w_WIRE_2;
    wire   w_WIRE_3;
        
    assign w_WIRE_1 = i_bit1 ^ i_bit2;
    assign w_WIRE_2 = w_WIRE_1 & i_carry;
    assign w_WIRE_3 = i_bit1 & i_bit2;

    assign o_sum   = w_WIRE_1 ^ i_carry;
    assign o_carry = w_WIRE_2 | w_WIRE_3;
   
endmodule