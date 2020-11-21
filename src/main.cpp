#include <stdio.h>
#include <string.h>

void ignore(char* buff, size_t* index, const char* toBeIgnored) {

}

int main(int argc, char** argv)
{
    FILE *fp;
    char line[255];
    size_t line_count = 0;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        puts("Error: Cannot read file ");
        puts(argv[1]);
        puts(" in read mode\n");
    }


    while (1) {
        line_count ++;
        if (fgets(line, 255, (FILE*)fp) == NULL)
            break;
        size_t len = strlen(line);
        if (len == 254) {
            puts("Warning: Lines with more than 255 characters are not recommended");
        }

        printf("Line %ld: %s", line_count, line);

        // Parsing one character at a time
        size_t index = 0;
        while (index < len) {
            ignore(line, &index, " ");
            index++;
        }
    }

    fclose(fp);
    return 0;
}