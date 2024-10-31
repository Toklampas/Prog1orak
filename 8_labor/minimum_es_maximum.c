void minmax(double tomb[], int n, double *min, double *max)
{
    *min = tomb[0];
    *max = tomb[0];
    for (int i = 0; i < n; i++)
    {
        if (tomb[i] < *min)
            *min = tomb[i];
        if (tomb[i] > *max)
            *max = tomb[i];
    }
}