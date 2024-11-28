typedef struct r {
   struct r *left, *right;
   char name[20+1]; // neve
   double w;        // vizhozama
} *river_tree;

#include <stdlib.h>
#include <string.h>

void fill(river_tree root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
        return;

    fill(root->left);
    fill(root->right);

    double left_w = root->left ? root->left->w : 0;
    double right_w = root->right ? root->right->w : 0;
    root->w = left_w + right_w;

    if (left_w >= right_w)
        strcpy(root->name, root->left->name);
    else
        strcpy(root->name, root->right->name);
    
}
