#include <stdio.h>

int main()
{
    char text[1000]={0}, c;
    int s, n, db=0, soreleje=0, utolso_szokoz=0;
    scanf("%c", &c);
    while (c != '#')
    {
        text[db] = c;
        db++;
        scanf("%c", &c);
    }
    scanf("%d%d", &s, &n);
    for (int i=0; i < s; i++)
    {
        for (int j=0; j <= n; j++)
            if (text[soreleje+j] == ' ')
                utolso_szokoz = soreleje + j;
        text[utolso_szokoz] = '\n';
        soreleje = utolso_szokoz + 1;
    }
    printf("%d", db-soreleje);
    return 0;
}