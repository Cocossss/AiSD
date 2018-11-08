#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "API.h"

#define MAX_SIZE 1024

int main(){

	int size1;
	int size2;
	int is_symm = 1;
	int is_equal = 1;
	BinTree tree1[MAX_SIZE] = {0};
	char TreeStr1[MAX_SIZE*2] = {0};
	BinTree tree2[MAX_SIZE] = {0};
        char TreeStr2[MAX_SIZE*2] = {0};

	printf("Hello! This is binary tree comparator. I define two binary trees as similar, equal, mirrored or  symmetric.\nEnter trees in bracket short form without spaces. Note: <empty tree> = '(#)'. Rules of short form:\n(<root> <tree> <#>) = (<root> <tree>)\n(<root> ##) = (<root>)\n");
	printf("1 tree: ");

	fgets(TreeStr1, MAX_SIZE*2, stdin);

	if (TreeStr1[strlen(TreeStr1) - 1] == '\n'){
		TreeStr1[strlen(TreeStr1) - 1] = '\0';
	}
	if (!(is_correct(TreeStr1))){
                return 0;
        }
	printf("2 tree: ");
        fgets(TreeStr2, MAX_SIZE*2, stdin);

	if (TreeStr2[strlen(TreeStr2) - 1] == '\n'){
                TreeStr2[strlen(TreeStr2) - 1] = '\0';
        }

	if (!is_correct(TreeStr2)){
                return 0;
        }

	printf("\nYou entered: %s\n             %s\n", TreeStr1, TreeStr2);


	CreateTree(tree1, TreeStr1, 0, 0);
	CreateTree(tree2, TreeStr2, 0, 0);

	printf("\nTree 1: \n");
	for(int i = 0; i < MAX_SIZE; i++){
		if (tree1[i].data != 0)
                	printf("   %d: left = %d, '%c', right = %d\n", i, tree1[i].left, tree1[i].data, tree1[i].right);
        }

	printf("Tree 2:\n");
        for(int i = 0; i < MAX_SIZE; i++){
		if (tree2[i].data != 0)
	                printf("   %d: left = %d, '%c', right = %d\n", i, tree2[i].left, tree2[i].data, tree2[i].right);
        }

	are_similar(tree1, tree2, 0, &is_equal);
	are_mirrored(tree1, tree2, 0, &is_symm);

return 0;
}
