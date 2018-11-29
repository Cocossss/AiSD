#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "API.h"
#define N 1000

// function to show recursion's calls
void Space(int level)
{

    for (int i = 0; i < level; i++)
        printf("   ");
    return;
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
    Space(level);
    printf("RotateRight\n");

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
    Space(level);
    printf("RotateLeft\n");

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

Node* InsertRoot(Node* tree, void* key, size_t size, int level)
{

    Space(level);
    printf("InsertRoot[level %d]: ", level);

    if (tree == NULL) { // make new elem if current node is empty

        tree = malloc(sizeof(Node));
        tree->key = key;
        tree->size = 1;
        tree->left = tree->right = NULL;
        fixsize(tree);

        if (size == sizeof(char))
            printf("push [%c]\n", *(char*)key);

        if (size == sizeof(float))
            printf("push [%g]\n", *(float*)key);

        return tree;
    }
    if (size == sizeof(float)) { // float case

        float num_key = *(float*)key; // saving float value of key

        if (num_key < *(float*)(tree->key)) { // if key < key of current node make recursion call for left subtree
            
            printf("%g < %g\n", num_key, *(float*)(tree->key));
            tree->left = InsertRoot(tree->left, key, size, level + 1);
            tree = RotateRight(tree, size, level + 1); // rotation right to move key in root

            return tree;
        }

        else { // else - make recursion call for right subtree
            
            printf("%g > %g\n", num_key, *(float*)(tree->key));
            tree->right = InsertRoot(tree->right, key, size, level + 1);
            tree = RotateLeft(tree, size, level + 1); // rotation left to move key in root

            return tree;
        }
    }
    if (size == sizeof(char)) { // char case
        char ch_key = *(char*)key; // saving char value of key
        char tree_key = *(char*)(tree->key);

        if ((int)ch_key - (int)tree_key < 0) {

            printf("%c < %c\n", ch_key, tree_key);
            tree->left = InsertRoot(tree->left, key, size, level + 1);
            tree = RotateRight(tree, size, level + 1);

            return tree;
        }
        else if ((int)ch_key - (int)tree_key >= 0) {

            printf("%c > %c\n", ch_key, tree_key);
            tree->right = InsertRoot(tree->right, key, size, level + 1);
            tree = RotateLeft(tree, size, level + 1);

            return tree;
        }
    }
}

Node* Insert(Node* tree, void* key, size_t size, int level)
{

    Space(level);
    printf("Insert[level %d]: ", level);

    if (tree == NULL) {

        tree = malloc(sizeof(Node));
        tree->key = key;
        tree->size = 1;
        tree->left = tree->right = NULL;
        fixsize(tree);

        if (size == sizeof(char))
            printf("push [%c]\n", *(char*)key);

        if (size == sizeof(float))
            printf("push [%g]\n", *(float*)key);

        return tree;
    }

    if (rand() % (tree->size + 1) == 0 && level == 0) { // if got chance for root inserting (1 out of tree->size + 1)

        printf("in root\n");
        return InsertRoot(tree, key, size, 0); //insert in root
    }

    else if (size == sizeof(float)) { // float case
        float num_key = *(float*)key;

        if (num_key < *(float*)(tree->key)) {
            
            printf("%g < %g\n", num_key, *(float*)(tree->key));
            tree->left = Insert(tree->left, key, size, level + 1);
        }

        else {
            
            printf("%g > %g\n", num_key, *(float*)(tree->key));
            tree->right = Insert(tree->right, key, size, level + 1);
        }
    }

    else if (size == sizeof(char)) { // char case

        char ch_key = *(char*)key;
        char tree_key = *(char*)(tree->key);

        if ((int)ch_key - (int)tree_key < 0) {

            printf("%c < %c  [%d]\n", ch_key, tree_key, (int)ch_key - (int)tree_key);
            tree->left = Insert(tree->left, key, size, level + 1);
        }

        else if ((int)ch_key - (int)tree_key >= 0) {

            printf("%c > %c [%d]\n", ch_key, tree_key, (int)ch_key - (int)tree_key);
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
        printf("[%g]  ", *(float*)(tree->key));

        if (tree->left != NULL)
            printf("left: [%g]  ", *(float*)(tree->left->key));
        else
            printf("left: [null]  ");

        if (tree->right != NULL)
            printf("right: [%g]\n", *(float*)(tree->right->key));
        else
            printf("right: [null]\n");

        if (tree->left != NULL)
            showtree(tree->left, size); // recursion call for left subtree

        if (tree->right != NULL)
            showtree(tree->right, size); // recursion call for right subtree

        return;
    }

    if (size == sizeof(char)) {
        printf("[%c]  ", *(char*)(tree->key));

        if (tree->left != NULL)
            printf("left: [%c]  ", *(char*)(tree->left->key));
        else
            printf("left: [null]  ");

        if (tree->right != NULL)
            printf("right: [%c]\n", *(char*)(tree->right->key));
        else
            printf("right: [null]\n");

        if (tree->left != NULL)
            showtree(tree->left, size);

        if (tree->right != NULL)
            showtree(tree->right, size);

        return;
    }
}

Node* Join(Node* left, Node* right)
{
    if (left == NULL)
        return right;

    if (right == NULL)
        return left;

    if (rand() % (left->size + right->size) < left->size) { // if left tree got chanse to be the root
        left->right = Join(left->right, right);
        fixsize(left);
        return left;
    }

    else { // else - right tree is root
        right->left = Join(left, right->left);
        fixsize(right);
        return right;
    }
}

Node* Remove(Node* tree, size_t size, char* to_delete, int* flag, int level)
{
    if (tree == NULL)
        return NULL;

    void* key;

    if (isalpha(to_delete[0]) && size == sizeof(char)) { // if type of RBST and element for deletion are char
        key = &to_delete[0];
    }

    else if (isdigit(to_delete[0]) && size == sizeof(float)) { // if type of RBST and element for deletion are float
        float num = strtod(to_delete, NULL);
        key = &num;
    }
    else { //  if type of RBST and element for deletion aren't same
        printf("Type of element for deletion doesn't match with type of BT! [%c]\n", *(char*)(tree->key));
        *flag = 2;
        return tree;
    }

    Space(level);
    printf("Remove[level %d]:  ", level);

    if (size == sizeof(float)) {
        float num_key = *(float*)(key);

        if (*(float*)(tree->key) == num_key) { // if key is found
            *flag = 1;
            Node* new_tree = Join(tree->left, tree->right); // join left and right subtree
            printf("delete [%g]\n", *(float*)(tree->key));
            free(tree);
            fixsize(new_tree);

            return new_tree;
        }

        printf("\n");

        if (num_key < *(float*)(tree->key)) // if key < current key, then search in left subtree
            tree->left = Remove(tree->left, size, to_delete, flag, level + 1);

        else // else - search in right subtree
            tree->right = Remove(tree->right, size, to_delete, flag, level + 1);
    }
    if (size == sizeof(char)) {

        char ch_key = *(char*)(key);

        if (*(char*)(tree->key) == ch_key) {
            *flag = 1;
            Node* new_tree = Join(tree->left, tree->right);
            printf("delete [%c]\n", *(char*)(tree->key));
            free(tree);
            fixsize(new_tree);

            return new_tree;
        }

        printf("\n");

        if (ch_key < *(char*)(tree->key))
            tree->left = Remove(tree->left, size, to_delete, flag, level + 1);

        else
            tree->right = Remove(tree->right, size, to_delete, flag, level + 1);
    }

    return tree;
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
