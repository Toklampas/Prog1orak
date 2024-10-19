#include <stdio.h>

void mail_merge(char *base, char *replace, char *out)
{
    int i = 0, j = 0;
    while (base[i] != '\0')
    {
        if (base[i] == '#')
        {
            int k = 0;
            while (replace[k] != '\0')
                out[j++] = replace[k++];
        }
        else
            out[j++] = base[i];
        i++;
    }
    out[j] = '\0';
}

int main()
{
    char base[] = "Oh #, miert vagy te #?";
    char replace[] = "Julia";
    char out[20];
    mail_merge(base, replace, out);
    printf("%s", out);
    return 0;
}