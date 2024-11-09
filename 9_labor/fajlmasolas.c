#include <stdio.h>
#include <stdlib.h>

int main()
{
    char in_name[30], out_name[30], c;
    FILE *in_file, *out_file;
    scanf("%s%s", in_name, out_name);
    in_file = fopen(in_name, "r");
    if(in_file == NULL)
        return 1;
    out_file = fopen(out_name, "w");
    if(out_file == NULL)
        return 1;
    while ((c = fgetc(in_file)) != EOF)
        fprintf(out_file, "%c", c);
    fclose(in_file);
    fclose(out_file);
    return 0;
}