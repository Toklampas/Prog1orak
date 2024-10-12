int twin_primes(int a, int b)
{
    int n = 0;
    for (int i = a; i <= b-2; i++)
        if (isprime(i) == 1 && isprime(i+2) == 1)
            n++;
    return n;
}