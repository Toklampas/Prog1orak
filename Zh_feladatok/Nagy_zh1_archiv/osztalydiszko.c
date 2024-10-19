#include <stdio.h>

typedef enum {BOY, GIRL} sex;

typedef struct
{
    sex sex;
    int height;
} student;

int partner(student a, student b)
{
    int dheight = a.height - b.height;
    if (dheight < 0)
        dheight = -dheight;
    if (a.sex != b.sex && dheight < 10)
        return 1;
    else return 0;
}

int num_partners(student *class, int lenght, int idx)
{
    int out=0;
    for (int i=0; i<lenght; i++)
        if (partner(class[idx], class[i]) == 1)
            out++;
    return out;
}

void tallest_and_partners(student *class, int lenght, int *tallest_idx, int *partners)
{
    int max=0;
    for (int i=0; i<lenght; i++)
        if (class[i].height > max)
        {
            max = class[i].height;
            *tallest_idx = i;
        }
    *partners = num_partners(class, lenght, *tallest_idx);
}

int main()
{
    student class[]={{BOY, 180}, {GIRL, 175}, {GIRL, 160}};
    int lenght = 3, tallest_idx, partners;
    tallest_and_partners(class, lenght, &tallest_idx, &partners);
    printf("%d %d", tallest_idx, partners);
    return 0;
}