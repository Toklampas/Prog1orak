void copy_next_word(char *str, char *out, int *str_i, int *out_i)
{
    if (str[*str_i] == ' ')
        (*str_i)++;
    while (str[*str_i] != ' ' && str[*str_i] != '\0')
    {
        out[*out_i] = str[*str_i];
        (*str_i)++;
        (*out_i)++;
    }
    if (str[*str_i] == ' ')
        out[(*out_i)++] = ' ';
}

void copy_nth_words(char *str, char *out, int n)
{
    int str_i=0, space=n, out_i=0;
    while (str[str_i] != '\0')
    {
        if (str[str_i] == ' ')
            space++;
        if (space == n)
        {
            copy_next_word(str, out, &str_i, &out_i);
            space = 0;
        }  
        else str_i++;
    }
    out[out_i] = '\0';
}

#include <stdio.h>

int main()
{
    char str[]="cica hollo varju kutya mokus beka csiga";
    char out[100];
    int n = 3;
    copy_nth_words(str, out, n);
    printf("%s", out);
    return 0;
}