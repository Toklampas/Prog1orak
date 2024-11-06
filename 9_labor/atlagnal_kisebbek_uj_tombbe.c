#include <stdlib.h>

int *filter_average(int tomb[], int n, int *newlength)
{
    if (n == 0) return NULL;
    int sum = 0, *out, j=0;
    *newlength = 0;
    for (int i=0; i<n; i++)
        sum += tomb[i];
    double average = (double)sum/n;
    for (int i=0; i<n; i++)
        if (tomb[i] < average)
            *newlength += 1;
    out = (int*)calloc(*newlength, sizeof(int));
    if (out == NULL) return NULL;
    for (int i=0; i<n; i++)
        if (tomb[i] < average)
        {
            out[j] = tomb[i];
            j++;
        }
    return out;
}

int main()
{
    int tomb[]={1, 2};
    int n = 2;
    int newsize;
    filter_average(tomb, n, &newsize);
    return 0;
}
