ghdl:
	ghdl -c *.vhd
	ghdl -r half_adder_tb --vcd=output.vcd

generate:
	g++ -Wall -g main.cpp -o test

clean:
	rm -f work-*.cf output.vcd
	rm -f test