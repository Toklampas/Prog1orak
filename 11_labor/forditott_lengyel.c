#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listelem {
    double value;
    struct listelem *next;
} listelem;

void push(listelem *stack, double a)
{
    listelem *new_elem = (listelem *)malloc(sizeof(listelem));
    new_elem->value = a;
    new_elem->next = stack->next;
    stack->next = new_elem;
}

double pop(listelem *stack)
{
    if (stack->next != NULL)
    {
        listelem *top = stack->next;
        double value = top->value;
        stack->next = top->next;
        free(top);
        return value;
    }
    return -1;
}

double evaluate(char *tokens[], int n)
{
    listelem stack;
    stack.next = NULL;

    for (int i = 0; i < n; i++) {
        char *token = tokens[i];
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
        {
            double b = pop(&stack);
            double a = pop(&stack);
            double result;

            if (strcmp(token, "+") == 0)
                result = a + b;
            else if (strcmp(token, "-") == 0)
                result = a - b;
            else if (strcmp(token, "*") == 0)
                result = a * b;
            else if (strcmp(token, "/") == 0)
                result = a / b;

            push(&stack, result);
        }
        else
        {
            double num = atof(token);
            push(&stack, num);
        }
    }

    double result = pop(&stack);
    return result;
}

int main()
{
    char *tokens[] = {"1", "2", "3", "4", "5", "+", "+", "+", "+"};
    int n = sizeof(tokens) / sizeof(tokens[0]);
    double result = evaluate(tokens, n);
    printf("Result: %f\n", result);
    return 0;
}