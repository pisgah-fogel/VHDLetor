all: cpp unit

ghdl:
	ghdl -a vhdl/*.vhd
	ghdl -e ripple_carry_adder_tb
	ghdl -r ripple_carry_adder_tb --vcd=output.vcd

iverilog:
	iverilog -o test -I verilog/ verilog/ripple_carry_adder_tb.v
	vvp test

cpp: generate unit
	g++ -Wall -g main.cpp -o test

unit:
	g++ -Wall -DUNIT -g ../UnitTest.cpp -o unit

generate:
	mkdir -p generated 
	python3 ../generate.py vhdl/ripple_carry_adder.vhd vhdl/full_adder.vhd

clean:
	rm -f work-*.cf output.vcd
	rm -f test unit
	rm -rf generated
