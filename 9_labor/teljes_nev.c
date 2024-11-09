#include <stdlib.h>

char * concatenate(char *strA, char *strB)
{
    int length = 0, i;
    for (i = 0; strA[i] != '\0'; i++)
        length += 1;
    for (i = 0; strB[i] != '\0'; i++)
        length += 1;
    length += 2;
    char *out = (char*)calloc(length, sizeof(char));
    for (i = 0; strA[i] != '\0'; i++)
        out[i] = strA[i];
    out[i++] = ' ';
    for (int j = 0; strB[j] != '\0'; j++)
        out[i++] = strB[j];
    out[i++] = '\0';
    return out;
}