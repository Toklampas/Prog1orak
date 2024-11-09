#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char letter;
    char code[6];
} codebook_t;

#define CODEBOOKSIZE 37
codebook_t codebook[CODEBOOKSIZE] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."}, {'G', "--."},
    {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."},
    {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"}, {'U', "..-"},
    {'V', "...-"}, {'W', "-.."}, {'X', "-..-"}, {'Y', "-.--"}, {'Z', "--.."},
    {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."},
    {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"}, {' ', " "}
};

char* morse(char* s) {
    int length = strlen(s);
    char *out = (char*)malloc(length*6+1);
    if(out == NULL)
        return NULL;
    out[0] = '\0';
    for (int i = 0; i < length; i++)
    {
        toupper(s[i]);
        if (s[i] == ' ')
            strcat(out, "  ");
        else
        {
            for (int j = 0; j < CODEBOOKSIZE; j++)
                if (codebook[j].letter == s[i])
                {
                    strcat(out, codebook[j].code);
                    strcat(out, " ");
                }
        }
    }
    int out_length = strlen(out);
    if (out_length > 0 && out[out_length - 1] == ' ')
        out[out_length - 1] = '\0';
    if (out_length != 0)
        out = realloc(out, out_length);
    return out;
}

int main()
{
    char text[] = "";
    morse(text);
    return 0;
}
