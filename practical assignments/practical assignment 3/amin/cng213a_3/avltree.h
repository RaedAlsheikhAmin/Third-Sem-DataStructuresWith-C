/*This is AVL tree header file
It contains functions needed to implement the tree in the code
as well as the declaration of the tree node.*/

#include <stdio.h>
#include <stdlib.h>
struct Tree //Tree has 3 pointers. Left, right, and next. "next" is to maintain the linked list in the node
{
	char name[100];//country name
	float mag,lat,lon;//magnitude, latitude, and longitude
	int tsu;//tsunami 
	struct Tree *left;//left child
	struct Tree *right;//right child
	struct Tree *next;//next pointer to maintain linked list the tree node
	int height;//height of the node
};
typedef struct Tree *tree;//declaring struct Tree as a pointer
int max(int a, int b) //this function is needed to maintain rotation functions. It returns maximum of 2 heights
{
	if (a >= b)
		return a;
	else
		return b;
}
/*height function is seperate in this code so that we don't face any crashes in our program
if we accidentally try to access t when t==NULL.*/
int height(tree t)
{
	if (t == NULL)
		return -1;
	else
		return t->height;
}
tree RRrotation(tree t1)
{
	tree t2;
	t2=t1->right;
	t1->right=t2->left;
	t2->left=t1;
	t1->height=max(height(t1->left), height(t1->right))+1;
	t2->height=max(height(t2->right),t1->height)+1;
	return t2;
}
tree LLrotation(tree t2)
{
	tree t1;
	t1=t2->left;
	t2->left=t1->right;
	t1->right=t2;
	t2->height=max(height(t2->left), height(t2->right))+1;
	t1->height=max(height(t1->left),t2->height)+1;
	return t1;
}
tree RLrotation(tree t3)
{
	t3->left=RRrotation(t3->left);
	return LLrotation(t3);
}
tree LRrotation(tree t3)
{
	t3->right=LLrotation(t3->right);
	return RRrotation(t3);
}
