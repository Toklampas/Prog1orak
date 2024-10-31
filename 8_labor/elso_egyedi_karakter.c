int first_unique(char str[])
{
    int characters[128] = {0};
    for (int i = 0; str[i] != '\0'; i++) 
        characters[str[i]] += 1;
    for (int i = 0; str[i] != '\0'; i++)
        if (characters[str[i]] == 1)
            return i;
    return -1;
}

int main()
{
    char str1[] = "alma";
    int test = first_unique(str1);
    return 0;
}