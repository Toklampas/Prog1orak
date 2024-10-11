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