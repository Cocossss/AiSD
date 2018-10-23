#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct List{
    char bracket;
    int index;
    struct List *next;
}List;

typedef struct Stack{
    struct List *head;
}Stack;

void push(Stack* stack, char br, int ind){

     List* list = malloc(sizeof(List));
     list->bracket = br;
     list->index = ind;
     list->next = stack->head;
     stack->head = list;
}

char pop(Stack* stack){

       if(stack->head == NULL)
               return 0;
       List* list = stack->head;
       char br = list->bracket;
       stack->head = list->next;
       free(list);

  return br;
}

char top(Stack stack){
     if (stack.head == NULL)
         return 0;
return stack.head->bracket;
}

int isEmpty(Stack stack){
   return stack.head == NULL;
}

int main(){

int is_wrong = 0;
int format;
char text[1002] = {0};
int wrong_symb[500];

printf("Hello! This is text's analyzer. I can check your text with brackets for correctness.\nValid brackets: '(', ')', '{', '}', '[', ']'.\nNote: max size of text - 1000 symbols.\n");

printf("Type '1', if you want input data from file input.txt, '2' - from the keyboard: ");
scanf("%d", &format);
char c = getchar();

if (format != 1 && format !=2){
	printf("Wrong input format!\n");
	return 0;
}

else if (format == 1){
	FILE *f;
	if ((f = fopen("input.txt", "r")) == NULL){
		printf("Couldn't open input.txt\n");
		return 0;
	}

	fgets(text, 1000, f);
	fclose(f);

}

else if (format == 2){
	printf("Enter your text: ");
	fgets(text, 1000, stdin);

}

printf("\n\nYou entered: %s\n", text);

Stack stack = {NULL};


int size = 0;
for(int i = 0; i < strlen(text); i++){

	if (text[i] == '('){
		push(&stack, text[i], i);
		printf("push: '%c' [index: %d]\n", text[i] , i);
	}

	if (text[i] == '{'){
                push(&stack, text[i], i);
                printf("push: '%c' [index: %d]\n", text[i] , i);
        }

	if (text[i] == '['){
                push(&stack, text[i], i);
                printf("push: '%c' [index: %d]\n", text[i] , i);
        }

	if (text[i] == ')'){

		if (top(stack) != '('){
			is_wrong = 1;
			wrong_symb[size] = i;
                        size++;
		}

		else{
			printf("pop: '('  current_br: ')' [index: %d]\n", i);
			pop(&stack);
		}

	}
	if (text[i] == '}'){

                if (top(stack) != '{'){
			is_wrong = 1;
			wrong_symb[size] = i;
                        size++;
                }

                else{
			printf("pop: '{'  current_br: '}' [index: %d]\n", i);
                        pop(&stack);
                }

        }
	if (text[i] == ']'){

                if (top(stack) != '['){
			is_wrong = 1;
			wrong_symb[size] = i;
                        size++;
                }

                else{
			printf("pop: '['  current_br: ']' [index: %d]\n", i);
                        pop(&stack);
                }

        }
}

	printf("\n\n");

        for(int i = 0; i < size; i++){
		printf("No opening bracket for '%c' [index: %d]\n", text[wrong_symb[i]], wrong_symb[i]);
	}

	while (top(stack) != 0){

		is_wrong = 1;
		printf("No closing bracket for '%c' [index: %d]\n", stack.head->bracket, stack.head->index);
		pop(&stack);

	}

if (is_wrong == 0){
	printf("\n\nText is correct \n");
}
else{
	printf("\n\nText isn't correct \n");
}

return 0;
}
