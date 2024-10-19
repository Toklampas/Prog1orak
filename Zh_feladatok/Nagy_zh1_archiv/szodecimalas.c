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
    int str_i=0, space=n-1, out_i=0;
    while (str[str_i] != '\0')
    {
        if (str[str_i] == ' ')
            space++;
        if (space == n-1)
        {
            copy_next_word(str, out, &str_i, &out_i);
            space = 0;
        }  
        str_i++;
    }
    out[out_i] = '\0';
}

int main()
{
    char str[]="cica hollo varju kutya mokus beka csiga";
    char out[17];
    int n = 3;
    copy_nth_words(str, out, n);
    return 0;
}