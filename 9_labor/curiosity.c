#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double fahrenheit_to_celsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5.0 / 9.0;
}

void convert_date_format(char *input_date, char *output_date)
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
    