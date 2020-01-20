#include <stdio.h>
#include <stdlib.h>
typedef enum { FALSE, TRUE } bool;
struct node {
	int val;
	int balance;
	struct node *left_child;
	struct node *right_child;
};
struct node* search(struct node *root, int key){
	if (root != NULL)
		if (key < root->val)
			root = search(root->left_child, key);
		else if (key > root->val)
			root = search(root->right_child, key);
	return(root);
}
struct node *insert(int key, struct node *root, bool *ht_inc){
	struct node *aroot;
	struct node *broot;
	if (root == NULL)
	{
		root = (struct node *) malloc(sizeof(struct node));
		root->val = key;
		root->left_child = NULL;
		root->right_child = NULL;
		root->balance = 0;
		*ht_inc = TRUE;
		return (root);
	}
	if (key < root->val)
	{
		root->left_child = insert(key, root->left_child, ht_inc);
		if (*ht_inc == TRUE)
		{
			switch (root->balance)
			{
			case -1: /* Right heavy */
				root->balance = 0;
				*ht_inc = FALSE;
				break;
			case 0: /* Balanced */
				root->balance = 1;
				break;
			case 1: /* Left heavy */
				aroot = root->left_child;
				if (aroot->balance == 1)
				{
					printf("Left to Left Rotation\n");
					root->left_child = aroot->right_child;
					aroot->right_child = root;
					root->balance = 0;
					aroot->balance = 0;
					root = aroot;
				}
				else
				{
					printf("Left to right rotation\n");
					broot = aroot->right_child;
					aroot->right_child = broot->left_child;
					broot->left_child = aroot;
					root->left_child = broot->right_child;
					broot->right_child = root;
					if (broot->balance == 1)
						root->balance = -1;
					else
						root->balance = 0;
					if (broot->balance == -1)
						aroot->balance = 1;
					else
						aroot->balance = 0;
					broot->balance = 0;
					root = broot;
				}
				*ht_inc = FALSE;
			}
		}
	}
	if (key > root->val)
	{
		root->right_child = insert(key, root->right_child, ht_inc);
		if (*ht_inc == TRUE)
		{
			switch (root->balance)
			{
			case 1: /* Left heavy */
				root->balance = 0;
				*ht_inc = FALSE;
				break;
			case 0: /* Balanced */
				root->balance = -1;
				break;
			case -1: /* Right heavy */
				aroot = root->right_child;
				if (aroot->balance == -1)
				{
					printf("Right to Right Rotation\n");
					root->right_child = aroot->left_child;
					aroot->left_child = root;
					root->balance = 0;
					aroot->balance = 0;
					root = aroot;
				}
				else
				{
					printf("Right to Left Rotation\n");
					broot = aroot->left_child;
					aroot->left_child = broot->right_child;
					broot->right_child = aroot;
					root->right_child = broot->left_child;
					broot->left_child = root;
					if (broot->balance == -1)
						root->balance = 1;
					else
						root->balance = 0;
					if (broot->balance == 1)
						aroot->balance = -1;
					else
						aroot->balance = 0;
					broot->balance = 0;
					root = broot;
				}/*End of else*/
				*ht_inc = FALSE;
			}
		}
	}
	return(root);
}
void display(struct node *root, int level){
	int i;
	if (root != NULL)
	{
		display(root->right_child, level + 1);
		printf("\n");
		for (i = 0; i < level; i++)
			printf("\t");
		printf("%d", root->val);
		display(root->left_child, level + 1);
	}
}
void inorder(struct node *root){
	if (root != NULL)
	{
		inorder(root->left_child);
		printf("%d ", root->val);
		inorder(root->right_child);
	}
}
main(){
	bool ht_inc;
	int key;
	int option;
	struct node *root = (struct node *)malloc(sizeof(struct node));
	root = NULL;
	while (1)
	{
		printf("1.Insert\n");
		printf("2.Display\n");
		printf("3.Quit\n");
		printf("Enter your option : ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			printf("Enter the value to be inserted : ");
			scanf("%d", &key);
			if (search(root, key) == NULL)
				root = insert(key, root, &ht_inc);
			else
				printf("Duplicate value ignored\n");
			break;
		case 2:
			if (root == NULL)
			{
				printf("Tree is empty\n");
				continue;
			}
			printf("Tree is : \n");
			display(root, 1);
			printf("\n\n");
			printf("Inorder Traversal is : ");
			inorder(root);
			printf("\n");
			break;
		case 3:
			exit(1);
		default:
			printf("Wrong option\n");
		}
	}
}