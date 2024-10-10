int ipow(int base, int exp)
{
    int out = base;
    for (int i = 0; i < exp-1; i++)
        out *= base;
    if (exp == 0)
        return 1;
    else return out;
}

int main()
{
    int a = ipow(3, 0);
}