int count_generic(char *str, int (*fuggveny)(char))
{
    int n = 0;
    while (*str)
    {
        if (fuggveny(*str))
            n++;
        str++;
    }
    return n;
}