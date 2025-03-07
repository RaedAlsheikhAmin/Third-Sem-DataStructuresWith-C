#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED



#endif // AVLTREE_H_INCLUDED
//this file is coming from the template that we had from odtu class, with some changes.

struct node//this node is going to make linked list and will be connected the duplicated countries with only the data.
{
    float ma,la,lo;//magnitude and latitude and longitude
    int ts;//tsunami
    struct node *next;//the linked list for the next one
};
struct tree
{
    char place[30];//countryname
    float ma,la,lo;//magnitude,latitude, longitude
    int ts;//tsunami
    struct tree *left;//left child
    struct tree *right;//right child
    struct node *side;//and this to connect the tree with the linked list
    int height;
};
typedef struct tree t;//to make it easier to use
typedef struct node n;//to make it easier to use

int AVLTreeHeight(struct tree * t)//to calculate the height of the tree
{
        if (t == NULL)
                return -1;
        else
                return t->height;
}
int Max(int x, int y)//max function to return max that helps us in the rotation to make AVL.
{
        if (x >= y)
                return x;
        else
                return y;
}
t* SingleRotateWithLeft(t* k2)//coming from the template
{
        t* k1;
        k1=k2->left;
        k2->left=k1->right;
        k1->right=k2;

        k2->height=Max(AVLTreeHeight(k2->left),AVLTreeHeight(k2->right))+1;
        k1->height=Max(AVLTreeHeight(k1->left),k2->height)+1;
        return k1;
}

t* SingleRotateWithRight(t* k1)
{
        t* k2;
        k2=k1->right;
        k1->right=k2->left;
        k2->left=k1;

        k1->height=Max(AVLTreeHeight(k1->left),AVLTreeHeight(k1->right))+1;
        k2->height=Max(AVLTreeHeight(k2->left),k1->height)+1;
        return k2;
}

t* DoubleRotateWithLeft(t* k3)
{
        k3->left= SingleRotateWithRight(k3->left);
        return SingleRotateWithLeft(k3);
}

t* DoubleRotateWithRight(t* k3)
{
        k3->right=SingleRotateWithLeft(k3->right);
        return SingleRotateWithRight(k3);
}
