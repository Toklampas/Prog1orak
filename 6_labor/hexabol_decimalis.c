#include <stdio.h>

int hexa_value(char c)
{
    if (c >= '0' && c <= '9')
        return c-'0';
    else if (c >= 'a' && c <= 'f')
        return 10+c-'a';
    else if (c >= 'A' && c <= 'F')
        return 10+c-'A';
    else return -1;
}

int main()
{
    char c;
    int dec;
    while (scanf("%c", &c) == 1)
        dec = dec * 16 + hexa_value(c);
    printf("%d", dec);
    return 0;
}