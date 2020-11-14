all: cpp unit

ghdl:
	ghdl -a *.vhd
	ghdl -e ripple_carry_adder_tb
	ghdl -r ripple_carry_adder_tb --vcd=output.vcd

cpp: generate unit
	g++ -Wall -g main.cpp -o test

unit:
	g++ -Wall -DUNIT -g ../UnitTest.cpp -o unit

generate:
	mkdir -p generated 
	python3 ../generate.py ripple_carry_adder.vhd full_adder.vhd

clean:
	rm -f work-*.cf output.vcd
	rm -f test unit
	rm -rf generated
