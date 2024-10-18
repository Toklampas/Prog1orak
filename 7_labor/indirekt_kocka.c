void cube(double sidelenght, double *area, double *volume)
{
    *area = sidelenght*sidelenght*6;
    *volume = sidelenght*sidelenght*sidelenght;
}

//main a teszteleshez
int main()
{
    double sidelength = 3.5;

    // memoriafoglalas az eredmenynek
    double area;
    double volume;

    cube(sidelength, &area, &volume);

    return 0;
}