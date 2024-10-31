#include <stdio.h>
#include <string.h>
	
enum { BUFFERSIZE = 128 };

int main(void) {
	char buffer[BUFFERSIZE], *c;
	fgets(buffer, BUFFERSIZE, stdin);   // read from stdin until newline
	c = strchr(buffer, '\n');           // replace newline with '\0'
	if (c != NULL)
		*c = '\0';
	reverse_words(buffer);              // call user function
	printf("%s", buffer);               // print the modified string
	return 0;
}

void reverse_words(char str[])
{
    int i = 0, start = 0;
    while (str[i] != '\0')
    {
        i++;
        if (str[i] == '\0' || str[i] == ' ')
        {
            int from = start, to = i-1;
            while (from < to)
            {
                char temp = str[from];
                str[from] = str[to];
                str[to] = temp;
                from++;
                to--;
            }
            start = i+1;
        }
    }
}