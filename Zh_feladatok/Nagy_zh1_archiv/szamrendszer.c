int str_lenght(char *str)
{
    int length = 0;
    while (*str != '\0')
    {
        length++;
        str++;
    }
    return length;
}

int value(char *str, int n)
{
    int exp = str_lenght(str)-1, sum = 0;
    for (int i = 0; i < str_lenght(str); i++)
    {
        int a = str[i]-'0';
        for (int j = 0; j < exp; j++)
            a *= n; 
        sum += a;
        exp--;
    }
    return sum;
}

int main()
{
    char str[] = "132";
    int n = 4;
    return value(str, n);
}