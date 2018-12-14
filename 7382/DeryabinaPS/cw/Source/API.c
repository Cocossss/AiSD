#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "API.h"
#define N 1000

int explore(int size, int *depth_mid, int *depth_wor){

        float* middle = calloc(size, sizeof(float));
        float* worst = calloc(size, sizeof(float));

        for(int i = 0; i < size; i++){
                middle[i] = rand()%(size*10);
                worst[i] = rand()%(size*10);
                if (i != 0){
                        while(worst[i] <= worst[i-1]){
                                worst[i] = worst[i-1] + 1 + rand()%10;
                        }
                }
        }

	char* ptr;

	Node* treeWR = NULL;
	Node* treeMR = NULL;

	treeWR = CreateRBST(treeWR, worst, ptr, sizeof(float), size);
	treeMR = CreateRBST(treeMR, middle, ptr, sizeof(float), size);

	*depth_mid = GetDepth(treeMR);
	*depth_wor = GetDepth(treeWR);

return 0;
}



// function to get char or float elements from srint str
int GetElements(float* keys, char* keys_ch, char* str, size_t fixtype)
{

    int size = 0;

    if (str[strlen(str) - 1] == '\n') // remove '\n' if it exists
        str[strlen(str) - 1] = '\0';

    if (fixtype == sizeof(char)) { // char case

        for (int i = 0; i < strlen(str); i++) {

            if (isalpha(str[i])) { // save char lelemte
                keys_ch[size] = str[i];
                size += 1;
                if (size >= N) {
                    printf("Max number of elements: %d!\n", N);
                    return 0;
                }
            }

            else if (str[i] == ' ' || str[i] == '\n') // skip spaces
                continue;

            else { // if string contains wrong symbols
                printf("Wrong input!\n");
                return 0;
            }
        }
    }
    if (fixtype == sizeof(float)) { // float case

        char* end = str;

        while (*str) {

            keys[size] = strtod(str, &end); // save float element
            size += 1;
            str = end;

            if (size >= N) {
                printf("Max number of elements: %d!\n", N);
                return 0;
            }

            while (!isdigit(*str) && *str) { // skip symbols that are not digits
                str++;
            }
        }
    }
    return size;
}

// fixing number of elements in tree
int fixsize(Node* tree)
{

    if (tree == NULL) {
        return 0;
    }

    tree->size = fixsize(tree->left) + fixsize(tree->right) + 1; // number elements of subtrees + 1 = number elements of tree
    return tree->size;
}

Node* RotateRight(Node* tree, size_t size, int level)
{
    Node* tmp = tree->left; // head of rotated tree is head of left subtree of tree

    if (tmp == NULL)
        return tree;

    tree->left = tmp->right; // replace left subtree  of tree with right subtree of rotated tree
    tmp->right = tree; // replace right subtree of rotated tree with tree
    tmp->size = tree->size + 1;
    fixsize(tree);

    return tmp;
}

Node* RotateLeft(Node* tree, size_t size, int level)
{
    Node* tmp = tree->right;

    if (tmp == NULL)
        return tree;

    if (size == sizeof(char) && *(char*)(tree->right->key) == *(char*)(tree->key)) // if keys of element and its right son is equal (char)
        return tree;

    if (size == sizeof(float) && *(float*)(tree->right->key) == *(float*)(tree->key)) // if keys of element and its right son is equal (float)
        return tree;

    tree->right = tmp->left;
    tmp->left = tree;
    tmp->size = tree->size;
    fixsize(tree);

    return tmp;
}

int GetDepth(Node* tree){

	if (tree == NULL)
		return 0;

	int left = 1;
	int right = 1;

	if (tree->left != NULL)
		left = left + GetDepth(tree->left);
	if (tree->right != NULL)
		right =  right + GetDepth(tree->right);

	if (right >= left)
		return right;
	else
		return left;


}

Node* CreateBST(Node* tree, float* keys_f, char* keys_ch, size_t type, int size){

for (int i = 0; i < size; i++) {

        if (type == sizeof(float)) {

                void * key = &keys_f[i];
                tree = Insert(tree, key, type, 0);
        }

        if (type == sizeof(char)) {
                void * key = &keys_ch[i];
        	tree = Insert(tree, key, type, 0);
	}

}
        return tree;
}


Node* CreateRBST(Node* tree, float* keys_f, char* keys_ch, size_t type, int size){


for (int i = 0; i < size; i++) {

        if (type == sizeof(float)) {

		void * key = &keys_f[i];
        	if (tree != NULL && rand() % (tree->size + 1) == 0) { // if got chance for root inserting (1 out of tree->size + 1)

                	tree = InsertRoot(tree, key, type, 0); //insert in root
        	}

        	else{
        		tree = Insert(tree, key, type, 0);
        	}
        }

	if (type == sizeof(char)) {
		void * key = &keys_ch[i];
                if (tree != NULL && rand() % (tree->size + 1) == 0) { // if got chance for root inserting (1 out of tree->size + 1)

                        tree = InsertRoot(tree, key, type, 0); //insert in root
                }

                else{
                        tree = Insert(tree, key, type, 0);
                }
        }

}
	return tree;
}

Node* InsertRoot(Node* tree, void* key, size_t size, int level)
{

    if (tree == NULL) { // make new elem if current node is empty

        tree = malloc(sizeof(Node));
        tree->key = key;
        tree->size = 1;
        tree->left = tree->right = NULL;
        fixsize(tree);

        return tree;
    }
    if (size == sizeof(float)) { // float case

        float num_key = *(float*)key; // saving float value of key

        if (num_key < *(float*)(tree->key)) { // if key < key of current node make recursion call for left subtree
            
            tree->left = InsertRoot(tree->left, key, size, level + 1);
            tree = RotateRight(tree, size, level + 1); // rotation right to move key in root

            return tree;
        }

        else { // else - make recursion call for right subtree
         
            tree->right = InsertRoot(tree->right, key, size, level + 1);
            tree = RotateLeft(tree, size, level + 1); // rotation left to move key in root

            return tree;
        }
    }
    if (size == sizeof(char)) { // char case
        char ch_key = *(char*)key; // saving char value of key
        char tree_key = *(char*)(tree->key);

        if ((int)ch_key - (int)tree_key < 0) {

            tree->left = InsertRoot(tree->left, key, size, level + 1);
            tree = RotateRight(tree, size, level + 1);

            return tree;
        }
        else if ((int)ch_key - (int)tree_key >= 0) {

            tree->right = InsertRoot(tree->right, key, size, level + 1);
            tree = RotateLeft(tree, size, level + 1);

            return tree;
        }
    }
}

Node* Insert(Node* tree, void* key, size_t size, int level)
{

    if (tree == NULL) {

        tree = malloc(sizeof(Node));
        tree->key = key;
        tree->size = 1;
        tree->left = tree->right = NULL;
        fixsize(tree);

        return tree;
    }

    if (size == sizeof(float)) { // float case
        float num_key = *(float*)key;

        if (num_key < *(float*)(tree->key)) {
            
            tree->left = Insert(tree->left, key, size, level + 1);
        }

        else {
            
            tree->right = Insert(tree->right, key, size, level + 1);
        }
    }

    else if (size == sizeof(char)) { // char case

        char ch_key = *(char*)key;
        char tree_key = *(char*)(tree->key);

        if ((int)ch_key - (int)tree_key < 0) {

            tree->left = Insert(tree->left, key, size, level + 1);
        }

        else if ((int)ch_key - (int)tree_key >= 0) {

            tree->right = Insert(tree->right, key, size, level + 1);
        }
    }

    fixsize(tree);
    return tree;
}

void showtree(Node* tree, size_t size)
{
    if (tree == NULL) {
        printf("Tree is empty!\n");
        return;
    }

    if (size == sizeof(float)) {

        if (tree->left != NULL)
            printf("[%g] <-- ", *(float*)(tree->left->key));
        else
            printf("[null] <-- ");

	printf("[%g]", *(float*)(tree->key));

        if (tree->right != NULL)
            printf(" --> [%g]\n", *(float*)(tree->right->key));
        else
            printf(" --> [null]\n");

        if (tree->left != NULL)
            showtree(tree->left, size); // recursion call for left subtree

        if (tree->right != NULL)
            showtree(tree->right, size); // recursion call for right subtree

        return;
    }

    if (size == sizeof(char)) {

        if (tree->left != NULL)
            printf("[%c] <-- ", *(char*)(tree->left->key));
        else
            printf("[null] <-- ");

	printf("[%c]", *(char*)(tree->key));

        if (tree->right != NULL)
            printf(" --> [%c]\n", *(char*)(tree->right->key));
        else
            printf(" --> [null]\n");

        if (tree->left != NULL)
            showtree(tree->left, size);

        if (tree->right != NULL)
            showtree(tree->right, size);

        return;
    }
}

void delete_BT(Node* tree)
{

    if (tree == NULL)
        return;

    if (tree->left != NULL)
        delete_BT(tree->left);
    if (tree->right != NULL)
        delete_BT(tree->right);

    free(tree);
    return;
}
