#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "API.h"

#define N 1000
//#define EXPLORE

int main()
{
    srand(time(NULL)); // new settings for random number

    char* str = calloc(N*2, sizeof(char)); // string for keys of RBST
    char* keys_ch = NULL; // for char keys
    float* keys = NULL; // for float keys
    int size = 0; // number of keys
    void* key;
    void* WorstKey =  NULL;
    void* MiddleKeyR =  NULL;
    int flag = 0;
    int format; // format of input
    size_t fixtype = 0; // type of keys
    float* middle = NULL;
    float* worst = NULL;
    int WRDepth;
    int MRDepth;
    int WDepth;
    int MDepth;
    int times[6];
    FILE *f;

    printf("Hello! This is randomized binary search tree (RBST) explorer!\nAvailable type of elements: char, float, int\n");
    printf("Type '1', if you want input data from file 'input.txt'\nType '2' - from the keyboard\nType '3' - to generate input data: ");
    scanf("%d", &format);
    char c = getchar(); // takes '\n'

    if (format != 1 && format != 2 && format != 3) {
        printf("Wrong input format!\n");
        return 0;
    }

    else if (format == 1) { // input from file

        if ((f = fopen("input.txt", "r")) == NULL) {
            printf("Couldn't open input.txt\n");
            return 0;
        }

	fgets(str, N - 1, f);
	printf("You entered: %s\n", str);
        fclose(f);
    }
    else if (format == 2) {

        printf("Input elements of RBST: ");
        fgets(str, N - 1, stdin);
	printf("You entered: %s\n", str);
    }
    else if (format == 3){

	printf("Input number of elements (<=10000): ");
	scanf("%d", &size);
	c = getchar(); // takes '\n'

	if (size > 10000)
		return 0;

	f = fopen("output.txt", "a");
	fprintf(f, "\n\nИсследование рандомизированного бинарного дерева (RBST).\n\n");

	middle = calloc(size, sizeof(float));
	worst = calloc(size, sizeof(float));

	for(int i = 0; i < size; i++){
		middle[i] = rand()%(size*10);
		worst[i] = rand()%(size*10);
		if (i != 0){
			while(worst[i] <= worst[i-1]){
				worst[i] = worst[i-1] + 1 + rand()%10;
			}
		}
	}

	fprintf(f, "Результаты построения RBST и BST на одних исходных данных. Количество узлов: %d\n", size);
	fprintf(f, "\nRBST    \t\t\t\tBST\n");

    }
    if (isalpha(str[0])) {  // if first element of keys is symbol
        fixtype = (sizeof(char));
        keys_ch = malloc(N * sizeof(*keys_ch));
    }

    else if (isdigit(str[0])) { // if first element of keys is digit
        fixtype = (sizeof(float));
        keys = calloc(N, sizeof(float));
    }

    else if (format != 3){
        printf("wrong input!\n");
        return 0;
    }

    Node* treeR = NULL;
    Node* tree = NULL;
    Node* WorstTreeR = NULL;
    Node* MiddleTreeR = NULL;
    Node* WorstTree = NULL;
    Node* MiddleTree = NULL;

    if (size == 0)
        size = GetElements(keys, keys_ch, str, fixtype);  // extract elements from string

    if (format == 3){
	times[0] = clock();
	WorstTreeR = CreateRBST(WorstTreeR, worst, keys_ch, sizeof(float), size);
	times[1] = clock();
	MiddleTreeR = CreateRBST(MiddleTreeR, middle, keys_ch, sizeof(float), size);
	times[2] = clock();

	WRDepth = GetDepth(WorstTreeR);
	MRDepth = GetDepth(MiddleTreeR);

	delete_BT(WorstTreeR);
	delete_BT(MiddleTreeR);

	times[3] = clock();
	WorstTree = CreateBST(WorstTree, middle, keys_ch, sizeof(float), size);
	times[4] = clock();
        MiddleTree = CreateBST(MiddleTree, middle, keys_ch, sizeof(float), size);
	times[5] = clock();

	MDepth = GetDepth(MiddleTree);

	fprintf(f, "Глубина (худший): %d\t\t\tГлубина (худший): %d\nГлубина (случайный): %d\t\t\tГлубина (случайный): %d\n", WRDepth, size, MRDepth, MDepth);
	fprintf(f, "Время (худший): %.4f\t\t\tВремя (худший): %.4f\nВремя (случайный): %.4f\t\tВремя (случайный): %.4f\n", (float)(times[1] - times[0])/CLOCKS_PER_SEC, (float)(times[4]-times[3])/CLOCKS_PER_SEC, (float)(times[2] - times[1])/CLOCKS_PER_SEC, (float)(times[5] - times[4])/CLOCKS_PER_SEC);
	fclose(f);

	printf("\nRBST    \t\t\t\tBST\n");
	printf("Глубина (худший): %d\t\t\tГлубина (худший): %d\nГлубина (случайный): %d\t\t\tГлубина (случайный): %d\n", WRDepth, size, MRDepth, MDepth);
        printf("Время (худший): %.4f\t\t\tВремя (худший): %.4f\nВремя (случайный): %.4f\t\tВремя (случайный): %.4f\n", (float)(times[1] - times[0])/CLOCKS_PER_SEC, (float)(times[4]-times[3])/CLOCKS_PER_SEC, (float)(times[2] - times[1])/CLOCKS_PER_SEC, (float)(times[5] - times[4])/CLOCKS_PER_SEC);

    }

    else{
	times[0] = clock();
        treeR = CreateRBST(treeR, keys, keys_ch, fixtype, size);
	times[1] = clock();

	times[2] = clock();
        tree = CreateBST(tree, keys, keys_ch, fixtype, size);
        times[3] = clock();

	printf("\nRBST:\n");
        showtree(treeR, fixtype);
        printf("\nBST:\n");
	showtree(tree, fixtype);
	printf("\n\n");
	printf("RBST\t\t\t\tBST\n");
	printf("Depth: %d\t\t\tDepth: %d\n", GetDepth(treeR), GetDepth(tree));
	printf("Time: %.4f\t\t\tTime: %.4f\n", (float)(times[1]-times[0])/CLOCKS_PER_SEC, (float)(times[3]-times[2])/CLOCKS_PER_SEC);
    }

    int depths_mid[100] = {0};
    int depths_wor[100] = {0};
    int mid = 0;
    int wor = 0;

#ifdef EXPLORE

    for(int i = 0; i < 100; i++){
	explore(size, &depths_mid[i], &depths_wor[i]);
	mid += depths_mid[i];
	wor +=depths_wor[i];
    }

    printf("%d:\ndepth for worst: %g\ndepth for middle: %g\n", size, (float)(wor/100), (float)(mid/100));

#endif

    free(str);
    free(keys);
    free(keys_ch);
    delete_BT(tree);
    delete_BT(treeR);
    delete_BT(WorstTree);
    delete_BT(MiddleTree);
    free(worst);
    free(middle);


    return 0;
}
