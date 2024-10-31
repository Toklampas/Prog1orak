#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned length;
    unsigned char* number;
} big_number_t;

big_number_t create(char* s)
{
    int len = strlen(s);
    big_number_t result;
    result.length = (len + 1) / 2;
    result.number = (unsigned char*)calloc(result.length, sizeof(unsigned char));


    
}