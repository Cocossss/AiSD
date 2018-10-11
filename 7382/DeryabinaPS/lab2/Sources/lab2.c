#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "API.h"

int main(){

    double result;   // for result of expression
    char expression[100]; // arithmetic expression
    char arg_input[15];  // for reading 1 argument
    char y_n[10];  // contains "Y", if read from file
    FILE *input; // in case reading from file
    int size; // contains number of arguments in expression

    printf("Hello! This is some kind of a calculator.\nI can add(+), subtract(-), divide(/) and multiply(*) numbers.\nNote: (a-)=a, (a+)=a, (a/)=a, (a*)=a\n");
    printf("Woulde you like enter data from file input.txt (file must exist)? (Y/N): ");

    fgets(y_n, 8, stdin);  // read 'Y' or 'N'

    while(y_n[0] != 'Y' && y_n[0] != 'N')  // if read neither 'Y' or 'N' repeat reading
    {
	printf("(Y/N): ");
        fgets(y_n, 8, stdin);
    }

    if(y_n[0] == 'Y') // if read 'Y', open file input.txt
    {
	input = fopen("input.txt", "r");

	if(input == NULL)
	{
	    printf("Problem with opening file input.txt.\n");
	    return 0;
	}

	fgets(expression, 98, input);
    }
    else
    {
	printf("Enter postfix expression (something like ""(ab(cd*)+)"" ): ");
	fgets(expression, 98, stdin);
    }

    if(expression[strlen(expression)-1] == '\n')  // if string contains '\n', delete it
    {
	expression[strlen(expression)-1] = '\0';
    }

    printf("Your expression: %s\n", expression);

    if(!is_expression_correct(expression))  // cheking correctness
    {
	return 0;
    }

    printf("Enter arguments and their values, each with a new line (example:a 10): \n");

    size = get_vars(expression); // number of unique arguments
    Args args[size];  // array for arguments and their values

    for(int i = 0; i<size; i++)  // filling array with arguments and their values
    {
	if(y_n[0] == 'Y')
	{
	    fgets(arg_input, 13, input);
	}
	else
	{
	    fgets(arg_input, 13, stdin);
	}

	if(!is_arg_correct(arg_input))
	{
	    return 0;
	}
	args[i].var = arg_input[0];
	args[i].value = atof(arg_input+2);
    }

    if(y_n[0] == 'Y') // if file was opened, close it
    {
	fclose(input);
    }

    printf("\nForming list...\n\n");
    Node* list = createList(expression, 1);  // creating hierarchical list

    printf("\nCalculating...\n\n");
    result = to_calculate(args, list, size, 1);  //calculating expression

    FILE *f = fopen("./output.txt", "w+");  // writting result in output.txt
    fprintf(f, "Expression: %s\n", expression);

    for(int i = 0; i<size; i++)
    {
	fprintf(f, "%c = %g\n", args[i].var, args[i].value);
    }

    fprintf(f, "Expression is equally %g\n", result);
    fclose(f);

    printf("Deleting list...\n");  // deleting the list
    delete_list(&list, list->next);

    printf("\nYour expression is equally %g\n", result); // show the result


    return 0;
}


