int isin(int tomb[], int n, int input)
{
    for (int i = 0; i<n; i++)
        if (input == tomb[i])
            return 1;
    return 0;
}

int *intersection(int a[], int n_a, int b[], int n_b, int *newlength)
{
    *newlength = 0;
    int j=0;
    for (int i = 0; i<n_a; i++)
        *newlength += (isin(b, n_b, a[i]));
    int *out = (int*)calloc(*newlength, sizeof(int));
    for (int i = 0; i<n_a; i++)
        if (isin(b, n_b, a[i]))
        {
            out[j] = a[i];
            j++;
        }
    return out;
}