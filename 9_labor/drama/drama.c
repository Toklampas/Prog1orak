#include <stdio.h>
#include <string.h>

void make_uppercase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 'a' + 'A';
        i++;
    }
}

int main()
{
    char file_name[31], character_name[21], line[101], outfilename[21];
    int is_character_speaking = 0;
    FILE *input_file, *output_file;
    scanf("%s%s", file_name, character_name);
    input_file = fopen(file_name, "r");
    if (input_file == NULL)
        return 1;
    strcpy(outfilename, character_name);
    output_file = fopen(strcat(outfilename, ".txt"), "w");
    if (output_file == NULL)
        return 1;
    make_uppercase(character_name);
    while(fgets(line, 101, input_file) != 0)
    {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0' && is_character_speaking)
        {    
            is_character_speaking = 0;
            fprintf(output_file, "\n");
        }
        else if (line[0] == '\t' && is_character_speaking)
            fprintf(output_file, "%s\n", line + 1);
        else if (line[0] != '\t')
        {
            char name_in_line[21];
            strncpy(name_in_line, line, 20);
            is_character_speaking = (strcmp(line, character_name) == 0);
        }
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}