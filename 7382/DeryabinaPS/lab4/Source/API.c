#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "API.h"
#define MAX_SIZE 1024

void Space(int level)
{
    for (int i = 0; i < level; i++)
        printf("   ");
    return;
}

int are_similar(BinTree* bt1, BinTree* bt2, int level, int* is_equal)
{
    if (level == 0)
        printf("\nCheking for similarity and equality...\n\n");
    Space(level);
    printf("Comparing:  [%d]<-[%c]->[%d]  [%d]<-[%c]->[%d]\n", bt1[0].left,
        bt1[0].data, bt1[0].right, bt2[0].left, bt2[0].data, bt2[0].right);
    if (bt1[0].data != bt2[0].data)
        *is_equal = 0;
    if (bt1[0].left == bt2[0].left && bt1[0].left != -1) {
        if (are_similar(bt1 + bt1[0].left - bt1[0].size,
                bt2 + bt2[0].left - bt2[0].size, level + 1, is_equal)
            == 0)
            return 0;
    }
    else if (bt1[0].left != bt2[0].left) {
        printf("\naren't similar\naren't equal\n");
        return 0;
    }
    if (bt1[0].right == bt2[0].right && bt1[0].right != -1) {
        if (are_similar(bt1 + bt1[0].right - bt1[0].size,
                bt2 + bt2[0].right - bt1[0].size, level + 1, is_equal)
            == 0)
            return 0;
    }
    else if (bt1[0].right != bt2[0].right) {
        printf("\naren't similar\naren't equal\n");
        return 0;
    }
    if (level == 0 && *is_equal == 0)
        printf("\nare similar\naren't equal\n");
    else if (level == 0 && *is_equal == 1)
        printf("\nare similar\nare equal\n");

    return 1;
}

int are_mirrored(BinTree* bt1, BinTree* bt2, int level, int* is_symm)
{
    int are_mir = 0;
    if (level == 0)
        printf("\nCheking for mirror similarity and symmetry...\n\n");

    Space(level);
    printf("Comparing:  [%d]<-[%c]->[%d]  [%d]<-[%c]->[%d]\n", bt1[0].left,
        bt1[0].data, bt1[0].right, bt2[0].left, bt2[0].data, bt2[0].right);

    if (bt1[0].data != bt2[0].data)
        *is_symm = 0;

    if (bt1[0].left != -1 && bt2[0].right != -1 && bt1[0].right == -1 && bt2[0].left == -1) {
        are_mir = 1;
        if (are_mirrored(bt1 + bt1[0].left - bt1[0].size,
                bt2 + bt2[0].right - bt2[0].size, level + 1, is_symm)
            == 0)
            return 0;
    }
    if (bt1[0].left == -1 && bt2[0].right == -1 && bt1[0].right != -1 && bt2[0].left != -1) {
        are_mir = 1;
        if (are_mirrored(bt1 + bt1[0].right - bt1[0].size,
                bt2 + bt2[0].left - bt2[0].size, level + 1, is_symm)
            == 0)
            return 0;
    }
    if (bt1[0].left != -1 && bt2[0].right != -1 && bt1[0].right != -1 && bt2[0].left != -1) {
        are_mir = 1;
        if (are_mirrored(bt1 + bt1[0].left - bt1[0].size,
                bt2 + bt2[0].right - bt2[0].size, level + 1, is_symm)
            == 0)
            return 0;
        if (are_mirrored(bt1 + bt1[0].right - bt1[0].size,
                bt2 + bt2[0].left - bt2[0].size, level + 1, is_symm)
            == 0)
            return 0;
    }
    if ((bt1[0].left == -1 && bt2[0].right == -1 && bt1[0].right == -1 && bt2[0].left == -1)) {
        if (level == 0 && *is_symm == 0)
            printf("\nare mirrored\naren't symmetrical\n");
        if (level == 0 && *is_symm == 1)
            printf("\nare mirrored\nare symmetrical\n");
        return 1;
    }
    if (are_mir == 0) {
        printf("\naren't mirrored\naren't symmetrical\n");
        return 0;
    }

    if (level == 0 && *is_symm == 0)
        printf("\nare mirrored\naren't symmetrical\n");
    if (level == 0 && *is_symm == 1)
        printf("\nare mirrored\nare symmetrical\n");
    return 1;
}

int CreateElem(BinTree* bt, char data, int size, int is_atom)
{
    if (size >= MAX_SIZE) {
        printf("Max depth of binary tree is 10!\n");
        return 0;
    }
    printf("created: %c\n", data);
    bt[size].data = data;
    if (is_atom == 1) {
        bt[size].left = -1;
        bt[size].right = -1;
        bt[size].size = size;
        return -1;
    }
    bt[size].left = size * 2 + 1;
    bt[size].right = size * 2 + 2;
    bt[size].size = size;
    return 1;
}

int CreateTree(BinTree* bt, char* str, int level, int size)
{
    if (level == 0)
        printf("\n\nCreating tree...\n");

    int LeftRight = 1;
    int is_empty = 0;
    if (level == 0)
        LeftRight = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '#') {
            LeftRight = 2;
            is_empty = 1;
        }
        if (str[i] == '(' && (str[i + 2] == '(' || str[i + 2] == '#')) {
            Space(level);
            printf("[levele %d]:", level);
            if (CreateElem(bt, str[i + 1], size * 2 + LeftRight, 0) == 0)
                return 0;
            CreateTree(bt, str + i + 2, level + 1, size * 2 + LeftRight);
            if (LeftRight == 1) {
                LeftRight = 2;
            }
            else {
                LeftRight = 1;
            }
            i++;
            int opening = 1;
            int closing = 0;
            while (opening != closing) {
                if (str[i] == '(') {
                    opening++;
                }
                if (str[i] == ')') {
                    closing++;
                }
                if (opening != closing) {
                    i++;
                }
            }
        }
        if (str[i] == '(' && str[i + 2] == ')') {
            Space(level);
            printf("[level %d]", level);
            if (CreateElem(bt, str[i + 1], size * 2 + LeftRight, 1) == 0)
                return 0;
            if (LeftRight == 1) {
                LeftRight = 2;
            }
            else {
                LeftRight = 1;
            }
        }
        if (str[i] == ')' && str[i + 1] == ')') {
            if (is_empty == 1) {
                bt[size].left = -1;
            }
            if (LeftRight == 2) {
                bt[size].right = -1;
            }
            return 0;
        }
    }
}

int is_correct(char* str)
{
    int opening = 1;
    int closing = 1;
    int elems = 0;

    if (str[0] != '(' && str[strlen(str) - 1] != ')') {
        printf("Expression isn't a Tree!\n");
        return 0;
    }
    else {
        opening += 1;
        closing += 1;
    }

    for (int i = 1; i < strlen(str) - 1; i++) {
        if ((str[i] != '(' && str[i] != ')' && str[i] != '#' && isalpha(str[i]) == 0) || (str[i] == ' ')) {
            printf("Wrong symbol: [%c]\n", str[i]);
            return 0;
        }

        if (isalpha(str[i]) || str[i] == '#') {
            elems += 1;
        }

        if (str[i] == '(') {
            opening += 1;
        }

        if (str[i] == ')') {
            closing += 1;
            if (closing > opening) {
                printf("Brackets are wrong!\n");
                return 0;
            }
        }

        if (isalpha(str[i]) && isalpha(str[i + 1]) || str[i] == '#' && (str[i + 1] == '#' || str[i + 1] != '(' && i != 1)) {
            printf("Expression isn't a Binary Tree!\n");
            return 0;
        }
    }

    if (opening != closing) {
        printf("Wrong brackets!\n");
        return 0;
    }

    if (elems == 0) {
        printf("Tree is empty!\n");
        return 0;
    }
    return elems;
}
