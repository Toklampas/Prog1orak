#include <stdio.h> 

int main()
{
int m, n, i=1;
scanf("%d%d", &m, &n);
while(m > 0)
{  
    while(i*m-n < 0)
        i++;
    printf("%d ", i);
    m = i*m-n;
    n = i*n;
}
return 0;
}

//nevezo n = i*n
//szamlalo m = i*m-n