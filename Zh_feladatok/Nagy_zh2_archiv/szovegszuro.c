#include <string.h>

char **string_select(char *in[], int in_meret, int *out_meret)
{
    int count = 0;
    
    for (int i = 0; i < in_meret; i++)
        if (in[i][0] >= 'A' && in[i][0] <= 'Z') 
            count++;

    char **out = (char **)malloc(count * sizeof(char *));
    int j = 0;

    for (int i = 0; i < in_meret; i++)
        if (in[i][0] >= 'A' && in[i][0] <= 'Z')
        {
            out[j] = (char *)malloc(strlen(in[i]) + 1);
            strcpy(out[j], in[i]);
            j++;
        }

    *out_meret = count;
    return out;
}