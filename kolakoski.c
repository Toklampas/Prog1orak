#include <stdio.h>

int main()
{
    int sor[100]={1, 2};
    int input, loc1=1, loc2=0, next_number=2;
    scanf("%d", &input);
    while (loc2 < 99)
    {
        int block_size = sor[loc1];
        for (int i = 0; i < block_size && loc2 < 99; i++)
        {
            loc2++;
            sor[loc2] = next_number;
        }
        loc1++;
        next_number++;
        if (next_number > input)
            next_number = 1;
    }
    for (int i = 0; i < 100; i++)
        printf("%d ", sor[i]);
    return 0;
}