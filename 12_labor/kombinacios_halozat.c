typedef enum
{
	AND,
	OR,
	NAND,
	NOR,
	NOT,
	FALSE,
	TRUE
} type_t;

typedef struct g {
	type_t type;
	struct g *in1, *in2;
} gate_t, *gate_tree;

#include <stdlib.h>

int eval(gate_tree root)
{
    if (root == NULL)
        return 0;

    if (root->type == TRUE)
        return 1;
    else if (root->type == FALSE)
        return 0;
    else if (root->type == NOT)
        return !eval(root->in1);
    else if (root->type == AND)
        return eval(root->in1) && eval(root->in2);
    else if (root->type == OR)
        return eval(root->in1) || eval(root->in2);
    else if (root->type == NAND)
        return !(eval(root->in1) && eval(root->in2));
    else if (root->type == NOR)
        return !(eval(root->in1) || eval(root->in2));
    else
        return 0;
}