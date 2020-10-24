ghdl:
	ghdl -a *.vhd
	ghdl -e ripple_carry_adder_tb
	ghdl -r ripple_carry_adder_tb --vcd=output.vcd

cpp:
	g++ -Wall -g main.cpp -o test

generate:
	mkdir -p generated 
	python3 ../generate.py ripple_carry_adder.vhd full_adder.vhd
	g++ -Wall -g main.cpp -o test

test:
	g++ -Wall -DUNIT -g ../UnitTest.cpp -o test

clean:
	rm -f work-*.cf output.vcd
	rm -f test
	rm -rf generated
