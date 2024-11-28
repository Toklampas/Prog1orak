typedef struct _node {
    double data;
    struct _node* left;
    struct _node* right;
} node;

#include <stdlib.h>

int negatives(node *root)
{
    if (root == NULL)
        return 0;
    int count = (root->data < 0) ? 1 : 0;
    return count + negatives(root->left) + negatives(root->right);
}