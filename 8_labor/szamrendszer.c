unsigned str_to_num(char str[], unsigned n)
{
    unsigned out = 0;
    for (int i = 0; str[i] != '\0'; i++)
        out = out * n + (str[i] - '0');
    return out;
}