#include <stdio.h>

int main()
{
    char a;
    int space = 1;
    while(scanf("%c", &a) == 1)
    {
        if (a == ' ')
        {
            space = 1;
            printf("%c", a);
        } 
        else if (a >= 'A' && a <= 'Z' && space == 1)
        {
            printf("%c", a);
            while (a != ' ')
            {
                if (scanf("%c", &a) != 1) break;
                else if (a >= 'a' && a <= 'z')
                    printf("%c", a-'a'+'A');
                else
                    printf("%c", a);
            }
        }
        else
        {
            printf("%c", a);
            space = 0;
        }
    }
    return 0;
}