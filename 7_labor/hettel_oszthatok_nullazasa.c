void seven_to_zero(int tomb[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (*(tomb+i) % 7 == 0)
            *(tomb+i) = 0;
    }
}