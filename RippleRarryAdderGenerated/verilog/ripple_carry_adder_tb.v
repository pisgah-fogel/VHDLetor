`include "ripple_carry_adder.v"
 
module ripple_carry_adder_tb ();
 
    parameter WIDTH = 4;

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

        $dumpfile("output.vcd");
        $dumpvars; 
        $dumpon;
        $display("Start of the testcase");
        #10;
        r_ADD_1 = 4'b0000;
        r_ADD_2 = 4'b0100;
        #10;
        r_ADD_1 = 4'b1000;
        r_ADD_2 = 4'b0100;
        #10;
        r_ADD_1 = 4'b0100;
        r_ADD_2 = 4'b1100;
        #10;
        r_ADD_1 = 4'b1100;
        r_ADD_2 = 4'b1100;
        #10;
        $display("End of the testcase");
        $finish;
        $dumpoff;
    end
 
endmodule