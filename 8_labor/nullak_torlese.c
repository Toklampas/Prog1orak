int remove_zeros (int tomb[], int n)
{
    int to = 0;
    for (int i=0; i<n; i++)
    { 
        if(tomb[i]==0)
        {
            for(; tomb[i]==0 && i<n; i++);
            if(i+1>n)
                return to;
            tomb[to] = tomb[i];
            to++;
        }
        else
        {
            tomb[to] = tomb[i];
            to++;
        }
    }
    return to;
}

int main()
{
    //int tomb[] = {1, 0, 4, 0, 0, 6, 0, 5, 6, 1, 0, 5};
    int tomb[] = {2, -7, 5, 0, 21, 0};
    int a = remove_zeros(tomb, 6);
    return 0;
}