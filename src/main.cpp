#include <stdio.h>
#include <string.h>

#include <string> // C++ string

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
public:
    FileHandler(const char*);
    ~FileHandler();
    char getChar();
    bool moveForward(size_t);
    bool expect(const char*);
    void skipComments();
    bool endOfFile();
    size_t countSpaces();
    void parseFile();
};

void FileHandler::parseFile()
{
    while (!endOfFile()) {
        skipComments();
        countSpaces();
        if (expect("`")) {
            printf("Macro detected Line: %ld, Index: %ld\n", line_count, index);
            // TODO
        }
        else if (expect("module"))
        {
            printf("Module detected Line: %ld, Index: %ld\n", line_count, index);

            skipComments();
            
            if (countSpaces() < 1)
                puts("Warning: Space expected between keyword \"module\" and module's name\n");

            std::string moduleName;
            readName(&moduleName);
            printf("Debug: Module's name is %s\n", moduleName.c_str());
        }
        else {
            puts("Warning: Keyword not recognized: ");
            puts(line+index);
            puts("\n");
            break;
        }
    }
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
            index++;
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

void FileHandler::skipComments()
{
    // Skip comments like "// ... \n"
    if (line[index] == '/' && line[index+1] == '/') {
        printf("Debug: Skip // comment, line %ld\n", line_count);
        //fillBuffer();
        while(line[index] == '\n') {
            if (!moveForward(1)) {
                puts("Debug: The file ends with a comment: \"//\"\n");
                return;
            }
        }
        moveForward(1);
    }

    //while(line[index] != '/n' || line[index] != '/0') index++;
    
    // Skip comments like "/* ... */"
    if (line[index] == '/' && line[index+1] == '*') {
        index+=2;
        printf("Debug: Skipping /* comment, line %ld\n", line_count);
        while(!(line[index-1] == '*' && line[index] == '/')) {
            if (!moveForward(1)) {
                puts("Error: End of file reached before \"*/\"\n");
                // TODO: Raise error
            }
        }
        printf("Debug: End */ comment, line %ld\n", line_count);
    }
}

bool FileHandler::expect(const char* ref)
{
    size_t i;
    for(i=0; line[i+index] != '\0' && ref[i] != '\0'; i++) {
        if (ref[i] != line[i+index])
            return false;
    }
    index += i;
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
        puts("[x] Usage: ./program_name file_to_parse");
        exit(1);
    }
    FileHandler file(argv[1]);
    file.parseFile();
    return 0;
}