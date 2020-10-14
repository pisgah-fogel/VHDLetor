ghdl:
	ghdl -c *.vhd
	ghdl -r half_adder_tb --vcd=output.vcd

cpp:
	g++ -Wall -g main.cpp -o test

generate:
	mkdir -p generated 
	python3 ../generate.py half_adder.vhd
	g++ -Wall -g main.cpp -o test

clean:
	rm -f work-*.cf output.vcd
	rm -f test
	rm -rf generated