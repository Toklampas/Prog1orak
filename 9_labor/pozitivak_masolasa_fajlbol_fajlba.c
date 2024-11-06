#include <stdio.h>

int main()
{
    double n;
    FILE *input, *output; 
    input = fopen("numbers.txt", "r");
    if (input == NULL) return 1;
    output = fopen("positive_numbers.txt", "w");
    if (output == NULL) return 1;

    while (fscanf(input, "%lf", &n) == 1)
        if (n > 0)
            fprintf(output, "%.4f ", n);

    fclose(input);
    fclose(output);
    return 0;
}