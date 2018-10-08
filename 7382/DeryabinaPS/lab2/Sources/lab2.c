#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "API.h"

int main(){

    double result;   // for result of expression
    char expression[100];
    char args_input[15];  // for reading 1 argument
    char c;
    printf("Hello! This is some kind of a calculator.\nI can add(+), subtract(-), divide(/) and multiply(*) numbers.\nNote: (a-)=a, (a+)=a, (a/)=a, (a*)=a\nEnter postfix expression (something like ""(ab(cd*)+)"" ): ");
    fgets(expression, 98, stdin);
    if(expression[strlen(expression)-1] == '\n')
	expression[strlen(expression)-1] = '\0';

    printf("Your expression: %s\n", expression);

    if(!is_expression_correct(expression))  // cheking correctness
    {
	return 0;
    }

    printf("Enter arguments and their values, each with a new line (example:a 10): \n");
    int size = get_vars(expression); // number of unique arguments
    Args args[size];
    for(int i = 0; i<size; i++)  // filling array with arguments and their values
    {
	fgets(args_input,13,stdin);
	if(!is_arg_correct(args_input))
	{
	    return 0;
	}
	args[i].var = args_input[0];
	args[i].value = atof(args_input+2);
    }


    printf("\nForming list...\n\n");
    Node* list = createList(expression, 1);  // creating hierarchical list

    printf("\nCalculating...\n\n");
    result = to_calculate(args, list, size, 1);  //calculating expression

    printf("\nYour expression is equally %g\n", result);

    FILE *f = fopen("./output.txt", "w+");  // writting result in output.txt
    fprintf(f, "Expression: %s\n", expression);
	
    for(int i = 0; i<size; i++)
    {
	fprintf(f, "%c = %g\n", args[i].var, args[i].value);
    }
	
    fprintf(f, "Expression is equally %g\n", result);
    fclose(f);
	
    printf("Deleting list...\n\n");
    delete_list(&list, list->next);
	
return 0;
}

