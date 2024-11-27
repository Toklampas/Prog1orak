#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* left;
    struct _node* right;
} node;

node* uj_elem(int n)
{
    node* uj_elem = (node*)malloc(sizeof(node));
    uj_elem->data = n;
    uj_elem->left = NULL;
    uj_elem->right = NULL;
    return uj_elem;
}

void insert (node* root, int n)
{
    node* p = root;
    while(1)
    {
        if(n == p->data)
            return;
        else if(n < p->data)
        {
            if(p->left == NULL)
            {
                p->left = uj_elem(n);
                return;
            }
            else
            {
                p = p->left;
            }
        }    
        else
        {
            if(p->right == NULL)
            {
                p->right = uj_elem(n);
                return;
            }
            else
            {
                p = p->right;
            }
        }
    }
}
