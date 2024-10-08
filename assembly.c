#include <stdio.h>

int calc_distance(int head_x, int head_y, int dest_x, int dest_y)
{
    int x = dest_x - head_x;
    int y = dest_y - head_y;
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    if (x < y)
        return y;
    else 
        return x;
}

int main(void)
{
    int parts[5]={0}, tape, slot, head_x=0, head_y=0, dest_x, dest_y, distance=0, act_n=0;
    char action;
    while (scanf("%c", &action) != EOF)
    {
        if (action == 'L')
        {
            act_n++;
            scanf("%d%d", &tape, &slot);
            parts[tape-1]++;
            dest_x = -500;
            dest_y = 300*tape;
            distance += calc_distance(head_x, head_y, dest_x, dest_y);
            head_x = dest_x;
            head_y = dest_y;
        }
        if (action == 'P')
        {
            act_n++;
            scanf("%d%d%d", &dest_x, &dest_y, &slot);
            distance += calc_distance(head_x, head_y, dest_x, dest_y);
            head_x = dest_x;
            head_y = dest_y;
        }
    }
    printf("Assembly time: %.2lf s\nPart usage", (double)distance/5000+act_n*0.1);
    for (int i = 0; i < 5; i++)
    {
        printf("\n\tTape %d: %d", i+1, parts[i]);
    }
    return 0;
}