`include "ripple_carry_adder.v"
 
module ripple_carry_adder_tb ();
 
    parameter WIDTH = 2;

    reg [WIDTH-1:0] r_ADD_1 = 0;
    reg [WIDTH-1:0] r_ADD_2 = 0;
    wire [WIDTH:0]  w_RESULT;

    ripple_carry_adder #(.WIDTH(WIDTH)) ripple_carry_inst
    (
        .i_add_term1(r_ADD_1),
        .i_add_term2(r_ADD_2),
        .o_result(w_RESULT)
        );

    initial
    begin
        #10;
        r_ADD_1 = 2'b00;
        r_ADD_2 = 2'b01;
        #10;
        r_ADD_1 = 2'b10;
        r_ADD_2 = 2'b01;
        #10;
        r_ADD_1 = 2'b01;
        r_ADD_2 = 2'b11;
        #10;
        r_ADD_1 = 2'b11;
        r_ADD_2 = 2'b11;
        #10;
    end
 
endmodule