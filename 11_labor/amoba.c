char check(char tabla[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (tabla[i][0] == tabla[i][1] && tabla[i][1] == tabla[i][2] && tabla[i][0] != '.')
            return tabla[i][0];
        if (tabla[0][i] == tabla[1][i] && tabla[1][i] == tabla[2][i] && tabla[0][i] != '.')
            return tabla[0][i];
    }
    if (tabla[0][0] == tabla[1][1] && tabla[1][1] == tabla[2][2] && tabla[0][0] != '.')
        return tabla[0][0];
    if (tabla[0][2] == tabla[1][1] && tabla[1][1] == tabla[2][0] && tabla[0][2] != '.')
        return tabla[0][2];
    return '\0';
}

