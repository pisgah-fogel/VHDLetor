
import sys
from shutil import copyfile
import os
from parsed_file import ParsedFile

WorkingDirectory = "./"
VHDLetorDirectory = "../"
ExampleHppFile = "example.hpp"
OutputDirectory = WorkingDirectory+"generated/"

def parse_file(filename):
    file = ParsedFile()
    file.init()
    base=os.path.basename(filename)
    component_name = os.path.splitext(base)[0] # [1] = .vhd

    if os.path.splitext(base)[1] == ".vhd":
        file.setLangage("VHDL")
    if os.path.splitext(base)[1] == ".v":
        file.setLangage("Verilog")
    else:
        print(os.path.splitext(base)[1])
        print("Error: Input file ", filename, " is not VHDL (.vhd) nor Verilog (.v)")
        exit(1)

    hppFilename = OutputDirectory+component_name+".hpp"
    copyfile(VHDLetorDirectory+ExampleHppFile, hppFilename)

    file.setHppFile(hppFilename)
    file.setVHDLFile(filename)
    file.parse()

files_to_parse = []
count = 0
for arg in sys.argv:
    count += 1
    if count < 2:
        continue
    files_to_parse.append(arg)
    

print("File to parse: ", files_to_parse)

for file in files_to_parse:
    parse_file(file)
