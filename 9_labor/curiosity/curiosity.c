#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double convert_temperature(double F)
{
    return (F - 32) * 5.0 / 9.0;
}

void convert_date(char *input_date, char *output_date)
{
    int day, month, year, sec, min, hour;
    sscanf(input_date, "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &min, &sec);
    sprintf(output_date, "%04d.%02d.%02d %02d.%02d.%02d", year, month, day, hour, min, sec);
    return;
}

int main()
{
    char input_filename[21], output_filename[21], line[100];
    FILE *input_file, *output_file;
    scanf("%s%s", input_filename, output_filename);
    input_file = fopen(input_filename, "r");
    if(input_file == NULL)
        return 1;
    output_file = fopen(output_filename, "w");
    if(output_file == NULL)
        return 1;
    while (fgets(line, 100, input_file) != 0)
    {    
        if (strncmp(line, "MEASUREMENT_TIME", sizeof("MEASUREMENT_TIME")) == 0)
        {
            char old_date[20], new_date[20];
            sscanf(line + sizeof("MEASUREMENT_TIME"), "%s", old_date);
            convert_date(old_date, new_date);
            fprintf(output_file, "MERESI_IDO %s\n", new_date);
        }
        else if (strncmp(line, "TEMPERATURE", sizeof("TEMPERATURE")) == 0)
        {
            double F, C;
            sscanf(line + sizeof("TEMPERATURE"), "%lfF", &F);
            C = convert_temperature(F);
            fprintf(output_file, "HOMERSEKLET %.1fC\n", C);
        }
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}