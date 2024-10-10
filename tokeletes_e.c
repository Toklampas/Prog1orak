#include <stdio.h>

int perfect(int n)
{
    int sum;
    for (int i=1; i<=n/2; i++)
    {
        if (n % i == 0)
            sum += i;
    }
    if (sum == n)
        return 1;
    else return 0;
}

int main(void) {
    int in = 6;
    int out = perfect(in);
    printf("%d\n", out);
    return 0;
}
