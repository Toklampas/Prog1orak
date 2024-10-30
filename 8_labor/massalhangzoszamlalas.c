int is_vowel(char c)
{
    char vowels[5]={'a','e','i','o','u'};
    if (c >= 'A' && c <= 'Z')
        c = c-'A'+'a';
    for (int i = 0; i < 5; i++)
        if (c == vowels[i])
            return 1;
    return 0;
}

int count_vowels(char *str)
{
    int i = 0, count = 0;
    while (str[i] != '\0')
    {
        count += is_vowel(str[i]);
        i++;
    }
    return count;
}

int main()
{
    char str[]="uborkaleves";
    int a = count_vowels(str);
    return 0;
}