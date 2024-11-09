#include <stdio.h>
#include <string.h>

int main()
{
    char filename[31], character[21], line[101];
    FILE *input, *output;
    scanf("%s %s", filename, character);
    input = fopen(filename, "r");
    if (input == NULL)
        return 1;
    output = fopen(character, "w");
    if (output == NULL)
        return 1;
        
}