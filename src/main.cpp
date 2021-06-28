#include <stdio.h>
#include <string.h>

#include <string> // C++ string

enum SignalType {
	Internal,
	Input,
	Output
};

enum SignalNature {
	Reg,
	Wire
};

class Signal
{
public:
	enum SignalType type;
	enum SignalNature nature;
	std::string name;
	size_t size_1, size_2;
};

class FileHandler
{
private:
    FILE *fp;
    char line[255];
    const char* mFilename;
    size_t line_count = 0;
    bool fillBuffer();
    size_t index = 0;
    size_t stringLength = 0;
    bool eof = false;
    void readName(std::string*);
	void readInteger(long int* ptr);
	Signal readSignal();
public:
    FileHandler(const char*);
    ~FileHandler();
    char getChar();
    bool moveForward(size_t);
    bool expect(const char*);
    size_t skipComments();
    size_t skipAllCommentsAndSpaces();
    bool endOfFile();
    size_t countSpaces();
    void parseVerilog();
};

void FileHandler::parseVerilog()
{
    while (!endOfFile()) {
        skipAllCommentsAndSpaces();
        if (expect("`")) {
            printf("Macro detected Line: %ld, Index: %ld\n", line_count, index);
            // TODO
        }
        else if (expect("module"))
        {
            printf("Module detected Line: %ld, Index: %ld\n", line_count, index);

            if (skipAllCommentsAndSpaces() < 1)
                puts("Warning: Space expected between keyword \"module\" and module's name\n");

            std::string moduleName;
            readName(&moduleName);
            printf("Debug: Module's name is %s\n", moduleName.c_str());

            // Looking for '(' - Inputs/outputs declaration
            skipAllCommentsAndSpaces();
            // TODO add "#(" to define parameters
            if (expect("(")) {
                countSpaces();
                // Looping over inputs/outputs
                while (1) {
                    // TODO read inputs/outputs definition with optional reg/wire and [N:P]
                    if (line[index]==',') {
                        moveForward(1);
                        // TODO keep looping over inputs/outputs
                    } else if (line[index]==')') {
                        moveForward(1);
                        break;
                    }
                }

                if (!expect(";")) {
                    puts("Error: You need to end your module Example ( ... ) with a ;\n");
                }
            }

            // Internal signals
            skipAllCommentsAndSpaces();
            // TODO read input.output specification or internals wire/reg

			// Blocks
			// TODO read assign or always block

			// Here we expect endmodule
            skipAllCommentsAndSpaces();
            if (!expect("endmodule")) {
				printf("Error: \"endmodule\" expected at line %d\n", line_count);
			}
            skipAllCommentsAndSpaces();
        }
        else {
            puts("Warning: Keyword not recognized: ");
            puts(line+index);
            puts("\n");
            break;
        }
    }
}

Signal FileHandler::readSignal()
{
	Signal output;

	std::string entry_1;
	skipAllCommentsAndSpaces();
	readName(&entry_1);
	if (entry_1 == "input") {
		output.type = SignalType::Input;
		countSpaces();
		readName(&entry_1);
	}
	else if (entry_1 == "output") {
		output.type = SignalType::Output;
		countSpaces();
		readName(&entry_1);
	}
	else {
		output.type = SignalType::Internal;
	}

	if (entry_1 == "wire") {
		output.nature = SignalNature::Wire;
	}
	else if (entry_1 == "reg") {
		output.nature = SignalNature::Reg;
	} else {
		printf("Error: Signal type: %s unexpected, should be wire/reg\n", entry_1.c_str());
	}

	// Detect [N,M]
	countSpaces();

	if (line[index]=='[') {
		moveForward(1);
		countSpaces();
		long int arg1;
		readInteger(&arg1);
		output.size_1 = arg1;
		countSpaces();
		if (!expect(":")) {
			puts("Error: ':' expected in [ ... : ... ]\n");
		}
		countSpaces();
		// TODO read number
		long int arg2;
		readInteger(&arg2);
		output.size_2 = arg2;
		countSpaces();
		if (!expect("]")) {
			puts("Error: ']' expected in [ ... : ... ]\n");
		}
		countSpaces();
	} else {
		output.size_1 = 0;
		output.size_2 = 0;
	}

	readName(&output.name);
	countSpaces();
	if (!expect(";")) {
		puts("Error: ';' expected after signal declaration\n");
	}

	return output;
}

/**
 * @brief Read an integer in decimal from the buffer
 *
 * @args ptr pointer to the integer to be overwritten
 */
void FileHandler::readInteger(long int* ptr)
{
	std::string buffer;
	*ptr = 0;
	while (line[index] >= '0' && line[index] <= '9') {
		buffer.push_back(line[index]);
	}
	for (std::string::reverse_iterator rit=buffer.rbegin(); rit!=buffer.rend(); ++rit)
		*ptr += 10*(*rit - '0');
}
void FileHandler::readName(std::string* str)
{
    str->clear();
    while (line[index] != ' ' && line[index] != '\t' && line[index] != '\n')
    {
        if(
            (line[index] >= 'a' && line[index] <= 'z') ||
            (line[index] >= 'A' && line[index] <= 'Z') ||
            (line[index] >= '0' && line[index] <= '9') ||
            line[index] == '_'
            )
        {
            str->push_back(line[index]);
			moveForward(1);
        }
        else {
            printf("Error: Character '%c' is not valid for a variable", line[index]);
            break;
        }
    }
}

size_t FileHandler::countSpaces()
{
    size_t countSpacer = 0;
    while (line[index]==' ' || line[index]=='\n' || line[index]=='\t')
    {
        countSpacer++;
        moveForward(1);
    }
    return countSpacer;
}

bool FileHandler::endOfFile()
{
    if (line[index] == '\0' || eof) {
        eof = true;
        return true;
    }
    return false;
}

size_t FileHandler::skipAllCommentsAndSpaces()
{
    size_t sum=0;
    size_t tmp=0;
    do {
        tmp = countSpaces();
        tmp += skipComments();
        sum += tmp;
    } while (tmp != 0);
    return tmp;
}

size_t FileHandler::skipComments()
{
    size_t skipped = 0;
    // Skip comments like "// ... \n"
    if (line[index] == '/' && line[index+1] == '/') {
        printf("Debug: Skip // comment, line %ld\n", line_count);
        fillBuffer(); // skip the full line
        skipped += stringLength;
    }

    //while(line[index] != '/n' || line[index] != '/0') index++;
    
    // Skip comments like "/* ... */"
    if (line[index] == '/' && line[index+1] == '*') { // index+1 is either a character or \0
		moveForward(2);
        skipped += 2;
        printf("Debug: Skipping /* comment, line %ld\n", line_count);
        while(!(line[index-1] == '*' && line[index] == '/')) {
            if (!moveForward(1)) {
                puts("Error: End of file reached before \"*/\"\n");
                // TODO: Raise error
            }
            skipped++;
        }
        printf("Debug: End */ comment, line %ld\n", line_count);
        moveForward(1);
        skipped++;
    }
    return skipped;
}

bool FileHandler::expect(const char* ref)
{
    size_t i;
    for(i=0; line[i+index] != '\0' && ref[i] != '\0'; i++) {
        if (ref[i] != line[i+index])
            return false;
    }
	moveForward(i);
    return true;
}

bool FileHandler::moveForward(size_t numb)
{
    index += numb;
    if (index>=stringLength) {
        puts("Debug: Index too big: reading new line\n");
        size_t new_index = index - stringLength;
        if (!fillBuffer())
            return false;
        //moveForward(index-255);
        index = new_index;
    }
    return true;
}

char FileHandler::getChar()
{
    return line[index];
}

bool FileHandler::fillBuffer()
{
    line_count ++;
    bool result = ! (fgets(line, 255, (FILE*)fp) == NULL);
    stringLength = strlen(line);
    if (stringLength == 254) {
        puts("Warning: Lines with more than 255 characters are not recommended");
    } else if (stringLength == 0 || ! result) {
        eof = true;
    }
    printf("Line %ld read: %s", line_count, line);
    index = 0;
    return result;
}

FileHandler::FileHandler(const char* filename)
{
    mFilename = filename;
    puts("[i] Opening file ");puts(mFilename);puts("\n");
    fp = fopen(mFilename, "r");
    if (fp == NULL) {
        puts("Error: Cannot read this file\n");
    } else {
        fillBuffer();
    }
}

FileHandler::~FileHandler()
{
    puts("[i] Closing file ");puts(mFilename);puts("\n");
    fclose(fp);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        puts("[x] Usage: ./program_name file_to_parse\n");
        exit(1);
    }
    FileHandler file(argv[1]);
    file.parseVerilog();
    return 0;
}
