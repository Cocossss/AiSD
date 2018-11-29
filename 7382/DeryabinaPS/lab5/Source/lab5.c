#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "API.h"

#define N 1000

int main()
{
    srand(time(NULL)); // new settings for random number

    char* str = malloc(sizeof(char) * N * 2); // string for keys of RBST
    char* keys_ch = NULL; // for char keys
    float* keys = NULL; // for float keys
    int size = 0; // number of keys
    char to_delete[20]; // key for deletion
    void* key;
    int flag = 0;
    int format; // format of input
    size_t fixtype = 0; // type of keys

    printf("Hello! This is randomized binary search tree maker (RBST)!\nAvailable type of elements: char, float, int\n");
    printf("All elements of one RBST must be the same.\n");
    printf("Type '1', if you want input data from file 'input.txt', '2' - from the keyboard: ");
    scanf("%d", &format);
    char c = getchar(); // takes '\n'

    if (format != 1 && format != 2) {
        printf("Wrong input format!\n");
        return 0;
    }

    else if (format == 1) { // input from file

        FILE* f;

        if ((f = fopen("input.txt", "r")) == NULL) {
            printf("Couldn't open input.txt\n");
            return 0;
        }

        fgets(to_delete, 18, f);
        fgets(str, N - 1, f);
        fclose(f);
    }
    else if (format == 2) {

        printf("Input elemet for deletion: ");
        fgets(to_delete, 18, stdin);
        printf("Input elements of RBST: ");
        fgets(str, N - 1, stdin);
    }

    printf("You entered: %s\n", str);

    if (isalpha(str[0])) {  // if first element of keys is symbol
        fixtype = (sizeof(char));
        keys_ch = malloc(N * sizeof(*keys_ch));
    }

    else if (isdigit(str[0])) { // if first element of keys is digit
        fixtype = (sizeof(float));
        keys = calloc(N, sizeof(float));
    }

    else {
        printf("wrong input!\n");
        return 0;
    }

    Node* tree = NULL;

    size = GetElements(keys, keys_ch, str, fixtype);  // extract elements from string

    for (int i = 0; i < size; i++) {

        if (fixtype == sizeof(float)) {
            key = &keys[i]; // turn to void*
        }

        if (fixtype == sizeof(char)) {
            key = &keys_ch[i]; // turn to void*
        }

        tree = Insert(tree, key, fixtype, 0);
    }

    printf("\n\n");
    showtree(tree, fixtype);
    printf("\n\n");

    tree = Remove(tree, fixtype, to_delete, &flag, 0);

    if (flag != 0 && flag != 2) { // if element for deletion is deleted
        printf("\nRBST after deletion :\n\n");
        showtree(tree, fixtype);
    }

    if (flag == 0) {
        printf("Element for deletion isn't in RBST!\n");
    }

    free(str);
    free(keys);
    free(keys_ch);
    delete_BT(tree);

    return 0;
}
