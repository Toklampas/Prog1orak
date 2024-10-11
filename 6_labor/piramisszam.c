int pyramid(int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i++)
        sum += i*i;
    return sum;       
}

int main()
{
    int a = pyramid(3);
}