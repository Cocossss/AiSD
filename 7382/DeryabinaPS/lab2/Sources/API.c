#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "API.h"

#define LINE "\x1b[4m"
#define END "\x1b[0m"

// function takes string with arithmetic expression
// and returns number of unique arguments
int get_vars(char *str){

    char *unique_arg = calloc(strlen(str), sizeof(char));  // string for unique arguments
    int size = 0;
    for(int i = 0; i<strlen(str); i++)
    {
	if(isalpha(str[i]) && !strchr(unique_arg, str[i]))  // if argument isn't in unique_arg,
	{                                                   // function will add it.
	    unique_arg[size] = str[i];
	    size++;
	}
    }

    free(unique_arg);
return size; // size of unique_arg

}

// oper_or_var contains operation "+", "-", "/", "*" or an argument
// is_atom = 1 if node is atom
// level contains depth of resursion
Node* createNode(char oper_or_var, int is_atom, int level){

    Spaces(level);    // printing spaces to show recursion's work
    printf("createNode: [is_atom = '%d', ", is_atom);

    Node* tmp = malloc(sizeof(Node));  //  memory allocation for element of list
    tmp->is_atom = is_atom;

    if(isalpha(oper_or_var))  //filling element with data
    {
	tmp->var = oper_or_var;
	printf("var = '%c']\n", oper_or_var);
    }
    else
    {
	tmp->operation = oper_or_var;
	printf("operation = '%c']\n", oper_or_var);
    }

    tmp->next = NULL;
    tmp->sublist = NULL;

return tmp;
}

// str contains arithmetic expression
// level - depth of recursion
Node* createList(char *str, int level){

    Spaces(level);  // spaces to show recursion
    printf("%screateList: level %d%s\n", LINE, level, END);

    char substr[100];  // buffer for sublist
    strcpy(substr, str);
    Node* tmp;

    if(str[strlen(str)-3] != ')')
    {
	tmp = createNode(str[strlen(str)-2], 1, level);
    }
    else
    {
	tmp = createNode(str[strlen(str)-2], 0, level);
    }

    Node *head = tmp; // head contains current sublist

    for(int i = strlen(str)-3; i >= 0; i--)
    {
	if(str[i] == '(')  // end of sublist
        {
            return head;
        }

	if(str[i] == ')')  // start of sublist
	{
	    if(tmp->is_atom == 1)  // if current element is atom, function will allocate memory for sublist
	    {
		tmp->next = createNode(tmp->operation, 0, level);
		substr[i+1] = '\0';
	        tmp->next->sublist = createList(substr, level+1);
		Spaces(level);
		printf("%screateList: level %d%s\n", LINE, level, END);
                tmp=tmp->next;
	    }
	    else
	    {
		if(tmp->sublist != NULL)  // if sublist has been already created, allocate next element and sublist for it
		{
		    tmp->next = createNode(tmp->operation, 0, level);
		    substr[i+1] = '\0';
                    tmp->next->sublist = createList(substr, level+1);
		    Spaces(level);
		    printf("%screateList: level %d%s\n", LINE, level, END);
                    tmp=tmp->next;
		}
		else  // if sublist is NULL, allocate memory for it
		{
		    substr[i+1] = '\0';
                    tmp->sublist = createList(substr,level+1);
		    Spaces(level);
		    printf("%screateList: level %d%s\n", LINE, level, END);
		}
	    }

	    int start = 1; // number of ')'
	    int end = 0; // number of '('
	    i--; // move left to scip one ')'

            while(start != end) // block for passibg by sublists that have been written in list already
	    {
		if(str[i] == ')')
		    start++;

		if(str[i] == '(')
		    end++;

	        if(start != end)
		    i--;
	    }
	}
        if(str[i] != '(' && str[i] != ')') // if current element is argument, allocate memory for it
        {
	    tmp->next = createNode(str[i], 1, level);
	    tmp=tmp->next;
        }
    }
}

// array args contains unique arguments and their values
// list contains expression in form of list
// size contains size of array args
// level contains depth of recursion
double to_calculate(Args args[], Node *list, int size, int level){
    int is_operation = 1;  // first element of sublist is operation "-", "+", "*", "/"
    double sum = 0;
    double multi = 1;
    double div = 1;
    double sub = 0;
    char current_operation = list->operation;

    Spaces(level);
    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);

    while(list != NULL){

        if(current_operation == '+')
	{
            if(is_operation == 1) // first element of sublist
            {
	        if(list->is_atom == 0)
	        {
	            sum += to_calculate(args, list->sublist, size, level+1); // calculating sublist
		    Spaces(level);
		    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);
	        }
	        is_operation = 0;
            }
            else
	    {
	        if(list->is_atom == 0)
	        {
	            sum += to_calculate(args, list->sublist, size, level+1);
	            Spaces(level);
	  	    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);
	        }
		else
	        {
                    sum += get_value(args, list->var, size, level); // added element
	        }
	    }

	    list = list->next;

        }

        if(current_operation == '*'){
            if(is_operation == 1)
            {
                if(list->is_atom == 0)
                {
                    multi *= to_calculate(args, list->sublist, size, level+1);
                    Spaces(level);
	            printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);
                }

	        is_operation = 0;

            }
 	    else
	    {
	        if(list->is_atom == 0)
	        {
                    multi *= to_calculate(args, list->sublist, size, level+1);
		    Spaces(level);
		    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);
                }
                else
                {
                    multi *= get_value(args, list->var, size, level);
                }
	    }

	list = list->next;

    }
        if(current_operation == '/')
        {
	    if(is_operation == 1)
	    {
	        if(list->is_atom == 0)
	        {
                    if(list->next == NULL) // arguments are reversed, so the last argument is dividend
                    {
                        div *= to_calculate(args, list->sublist, size, level+1);
                    }
                    else // if argument isn't the last, it is divider
                    {
                        div *= 1/to_calculate(args, list->sublist, size, level+1);
                    }

		    Spaces(level);
		    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);

 	        }

	        is_operation = 0;

            }
	    else
	    {
	        if(list->is_atom == 0)
	        {
	            if(list->next == NULL) // is dividend
                    {
                        div *= to_calculate(args, list->sublist, size, level+1);
                    }
                    else // id divider
                    {
                        div *= 1/to_calculate(args, list->sublist, size, level+1);
                    }

		    Spaces(level);
		    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);

	        }
	        else
	        {
                    if(list->next == NULL)
                    {
                        div *= get_value(args, list->var, size, level);
                    }
                    else
                    {
                        div *= 1/get_value(args, list->var, size, level);
                    }
                }
	    }

	    list = list->next;

        }

	if(current_operation == '-')
	{
            if(is_operation == 1)
            {
                if(list->is_atom == 0)
                {                           // arguments for "-" are also reversed
       		    if(list->next == NULL)  // if argument is the last, it is positive
		    {
		        sub += to_calculate(args, list->sublist, size, level+1);
		    }
		    else // if element isn't the last, it is negative
		    {
		        sub -= to_calculate(args, list->sublist, size, level+1);
		    }

		Spaces(level);
		printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);

                }

                is_operation = 0;

            }
	    else
	    {
                if(list->is_atom == 0)
                {
		    if(list->next != NULL)
		    {
			sub -= to_calculate(args, list->sublist, size, level+1);
		    }
		    else
		    {
			sub += to_calculate(args, list->sublist, size, level+1);
		    }

		    Spaces(level);
		    printf("%sto_calculate: level %d, current_operation: '%c'%s\n", LINE, level, current_operation, END);

                }
                else
                {
		    if(list->next != NULL)
		    {
			sub -= get_value(args, list->var, size, level);
		    }
		    else
		    {
			sub += get_value(args, list->var, size, level);
		    }
                }
	    }

	    list = list->next;

        }
    }

    Spaces(level);
    // to return value of certain sublist:
    if(current_operation == '/')
    {
	printf("Result of this level: %lg\n", div);
	return div;
    }
    if(current_operation == '+')
    {
	printf("Result of this level: %lg\n", sum);
	return sum;
    }
    if(current_operation == '*')
    {
	printf("Result of this level: %lg\n", multi);
	return multi;
    }
    if(current_operation == '-')
    {
	printf("Result of this level: %lg\n", sub);
	return sub;
    }
}

// print spaces accordint to the depth of recursion
void Spaces(int level){

    for(int i = 0; i < level; i++)
    {
        printf("   ");
    }

    return;

}

// function takes 1 argument - arithmetic expression
int is_expression_correct(char *str){

    int opening = 0; // number if "("
    int closing = 0; // number of ")"
    int args = 0; // number of arguments in exppression

    if(str[0] != '(' || str[strlen(str)-1] != ')')
    {
	printf("Brackets are not enough!\n");
	return 0;
    }

    for(int i = 0; i < strlen(str); i++)
    {
	if(isalpha(str[i]))
	{
	    args += 1;
	}

	if(str[i] == '(')
	{
	    opening += 1;
	}

	if(str[i] == ')')
	{
	    closing += 1;
	}

	if(str[i] == ' ')
	{
	    printf("Unacceptable symbol: ' '!\n");
	    return 0;
	}

	if(str[i] == ')' && !(str[i-1] == '/' || str[i-1] == '*' || str[i-1] == '+' || str[i-1] == '-'))
	{
	    printf("Operation before the bracket ')' is missed!\n");
	    return 0;
	}

	if(str[i] != '(' && str[i] != ')' && str[i+1] != ')' && !isalpha(str[i]))
	{
	    printf("Arguments must be a letter (a, b, c,..)!\n");
	    return 0;
	}
    }
    if(opening != closing)
    {
	printf("Number of opening and closing brackets must be same!\n");
	return 0;
    }

    if(args == 0)
    {
	printf("Where are arguments??\n");
	return 0;
    }

return 1;
}

// array args contains unique arguments and their values
// var contains argument, whose value needed
// size of array args
// level - depth of recursion
double get_value(Args args[], char var, int size, int level){

    for(int i = 0; i < size; i++)
    {
	if(args[i].var == var) // value is found
	{
	    Spaces(level);
	    printf("Argument='%c', value=%g\n", args[i].var, args[i].value);

	    return args[i].value;
	}
    }

    printf("You didn't enter value for var '%c', so lets suppose %c=1 :)\n", var, var); // or not found
    return 1;
}

//function takes string with 1 argument and its value
int is_arg_correct(char* str){

    int minos; // contains index of '-'

    if(str[strlen(str)-1] == '\n')
    {
	str[strlen(str)-1] = '\0';
    }

    if(!isalpha(str[0]))
    {
	printf("Arguments must be a letter!\n");
	return 0;
    }

    if(str[1] != ' ')
    {
	printf("Space between argument and its value!\n");
	return 0;
    }

    if(str[2] == '-')
    {
	minos = 3;
    }
    else
    {
	minos = 2;
    }

    for(int i = minos; i<strlen(str); i++)
    {

	if(str[i] == '.')
	{
	    continue;
	}

	if(!isdigit(str[i]))
	{
	    printf("Values must be a number!\n");
	    return 0;
	}
    }

    return 1;
}

void delete_list(Node** first, Node* second){

    while(second != NULL)
    {
	if((*first)->is_atom == 0)
	{
	   delete_list(&(*first)->sublist, (*first)->sublist->next);
	}
	printf("[free %c]\n", (*first)->var);
 	free(*first);
	*first = second;
	second = second->next;
    }

    if((*first)->is_atom == 0)
    {
	delete_list(&(*first)->sublist, (*first)->sublist->next);
    }

    printf("[free %c]\n", (*first)->var);
    free(*first);
    return;

}
