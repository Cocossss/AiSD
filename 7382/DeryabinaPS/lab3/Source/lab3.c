#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct List {
    char bracket; // symbol of bracket
    int index; // symbol's index in string
    struct List* next;
} List;

typedef struct Stack {
    struct List* head; // top of stack
} Stack;

void push(Stack* stack, char br, int ind)
{

    List* list = malloc(sizeof(List)); // new element in list
    list->bracket = br;
    list->index = ind;
    list->next = stack->head; // new element is top of list
    stack->head = list; // top of stack is new element
    printf("push:   '%c' [index: %d] is top of stack\n", br, ind);
}

char pop(Stack* stack)
{

    if (stack->head == NULL) // if stack is empty
        return 0;
    List* list = stack->head; // save contain of top of stack
    char br = list->bracket;
    stack->head = list->next; // top of stack is next element in list
    printf("pop: bracket: '%c', index: %d \n", br, list->index);
    if (stack->head != NULL)
        printf("'%c' [index: %d] is top of stack\n", stack->head->bracket, stack->head->index);
    else
        printf("stack is empty\n\n");
    free(list);

    return br;
}

char top(Stack stack)
{
    if (stack.head == NULL) // if stack is empty
        return 0;
    return stack.head->bracket;
}

int isEmpty(Stack stack)
{
    return stack.head == NULL;
}

int main()
{

    int is_wrong = 0;
    int format;
    char text[1002] = { 0 };
    int wrong_symb[500]; // contains index of closing bracket, that hasn't match opening bracket

    printf("Hello! This is text's analyzer. I can check your text with brackets for correctness.\nValid brackets: '(', ')', '{', '}', '[', ']'.\nNote: max size of text - 1000 symbols.\n");

    printf("Type '1', if you want input data from file input.txt, '2' - from the keyboard: ");
    scanf("%d", &format);
    char c = getchar(); // takes '\n'

    if (format != 1 && format != 2) {
        printf("Wrong input format!\n");
        return 0;
    }

    else if (format == 1) { // inpit from file
        FILE* f;
        if ((f = fopen("input.txt", "r")) == NULL) {
            printf("Couldn't open input.txt\n");
            return 0;
        }

        fgets(text, 1000, f);
        fclose(f);
    }

    else if (format == 2) { // input from the keyboard
        printf("Enter your text: ");
        fgets(text, 1000, stdin);
    }

    printf("\n\nYou entered: %s\n", text);

    Stack stack = { NULL }; // init stack

    int size = 0; // size for wrong_symb

    printf("Analysing text...\n\n");

    for (int i = 0; i < strlen(text); i++) {

        if (text[i] == '(') { // push opening brackiet in stack
            push(&stack, text[i], i);
        }

        if (text[i] == '{') { // push opening brackiet in stack
            push(&stack, text[i], i);
        }

        if (text[i] == '[') { // push opening brackiet in stack
            push(&stack, text[i], i);
        }

        if (text[i] == ')') {

            if (top(stack) != '(') { // if types of brackets aren't same
                is_wrong = 1;
                wrong_symb[size] = i;
                size++;
            }

            else {
                printf("\ncurrent bracket: '%c', index %d\n", text[i], i);
                pop(&stack);
            }
        }
        if (text[i] == '}') {

            if (top(stack) != '{') { // if types of brackets aren't same
                is_wrong = 1;
                wrong_symb[size] = i;
                size++;
            }

            else {
                printf("\ncurrent bracket: '%c', index %d\n", text[i], i);
                pop(&stack);
            }
        }
        if (text[i] == ']') {

            if (top(stack) != '[') { // if types of brackets aren't same
                is_wrong = 1;
                wrong_symb[size] = i;
                size++;
            }

            else {
                printf("\ncurrent bracket: '%c', index %d\n", text[i], i);
                pop(&stack);
            }
        }
    }

    printf("\n\n");

    for (int i = 0; i < size; i++) { // printing closing brackets, that hasn't opening brackets
        printf("No opening bracket for '%c' [index: %d]\n", text[wrong_symb[i]], wrong_symb[i]);
    }

    if (top(stack) != 0)
        printf("Freeing stack...\n\n");

    while (top(stack) != 0) { // printint opening brackets, that hasn't closing brackets

        is_wrong = 1;
        printf("No closing bracket for '%c' [index: %d]\n", stack.head->bracket, stack.head->index);
        pop(&stack);
    }

    FILE *f = fopen("output.txt", "w");

    if (is_wrong == 0) {
        printf("\n\nText is correct \n");
	fprintf(f, "You entered: %s\n\nText is correct\n", text);
    }
    else {
        printf("\n\nText isn't correct \n");
        fprintf(f, "You entered: %s\n\nText isn't correct\n", text);
    }

    fclose(f);

    return 0;
}
