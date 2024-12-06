int jail(int cells[])
{
    int n = 0, from = 9, to = 0;
    while(1)
    {
        for (; cells[from] == 0; from--);
        for (; cells[to] == 10; to++);
        if (from <= to) break;
        cells[from]--;
        cells[to]++;
        if ((from - to) % 2 != 0) n++;
    }
    return n;
}