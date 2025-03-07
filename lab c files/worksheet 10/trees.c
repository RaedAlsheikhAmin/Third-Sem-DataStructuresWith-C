/*
Breadth-first traversal

There is only one type : level order traversal
Visit all the nodes from top to bottom from left to right



Depth-first traversal

There are 3 types : pre-order, in-order, post-order

Pre-order - Visit the parent, then left, then right
In-order - Visit the left, then parent, then right
Post-order - Visit the left, then right, then parent
*/
#include <stdio.h>
#include <stdlib.h>
struct node
{
	int val;
	struct node *left;
	struct node *right;
};
struct node* insert(struct node*,int);
struct node* rem(struct node*,int);
int search(struct node*,int);
int min(struct node*);
int max(struct node*);
int main()
{
	struct node *root=NULL;
	int ch=0,val;
	while(ch!=6)
	{
		printf("\n1.Insert\n2.Search\n3.Find minimum value\n4.Find maximum\n5.Delete\n6.Exit\nChoose:");
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("Enter the value:");
			scanf("%d",&val);
			root=insert(root,val);
		}
		else if(ch==2)
		{
			printf("Enter the value:");
			scanf("%d",&val);
			if(search(root,val))
			{
				printf("\nThe value %d is in the tree.\n",val);
			}
			else
			{
				printf("\nThe value %d is not in the tree.\n",val);
			}
		}
		else if(ch==3)
		{
			printf("\nThe minimum of this tree is %d\n",min(root));
		}
		else if(ch==4)
		{
			printf("\nThe maximum of this tree is %d\n",max(root));
		}
		else if(ch==5)
		{
			printf("Enter the value:");
			scanf("%d",&val);
			root=rem(root,val);
		}
	}
}
int max(struct node *root)
{
	if(root==NULL)
	{
		printf("\nThe tree is empty\n");
		return -1;
	}
	else if(root->right==NULL)
	{
		return root->val;
	}
	else if(root->right!=NULL)
	{
		return max(root->right);
	}
}
int min(struct node *root)
{
	if(root==NULL)
	{
		printf("\nThe tree is empty\n");
		return -1;
	}
	else if(root->left==NULL)
	{
		return root->val;
	}
	else if(root->left!=NULL)
	{
		return min(root->left);
	}
}
struct node* insert(struct node *root,int val)
{
	if(root==NULL)
	{
		root=(struct node*) malloc(sizeof(struct node));
		root->val=val;
		root->right=NULL;
		root->left=NULL;
		return root;
	}
	else if(val<root->val)
	{
		root->left=insert(root->left,val);
	}
	else if(val>root->val)
	{
		root->right=insert(root->right,val);
	}
	else
	{
		printf("\nThe value %d is already in the tree.\n");
	}
	return root;
}
int search(struct node *root, int val)
{
	if(root==NULL)
	{
		return 0;
	}
	else if(val>root->val)
	{
		return search(root->right,val);
	}
	else if(val<root->val)
	{
		return search(root->left,val);
	}
	else
	{
		return 1;
	}
}
