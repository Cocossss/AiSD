typedef struct Node{
    union{
	char operation;
	char var;
    };
    int is_atom;
    struct Node *next;
    struct  Node *sublist;
} Node;

typedef struct  Args{
    double value;
    char var;
}Args;

Node* createNode(char oper_or_var, int is_atom, int level);
Node* createList(char *str, int level);
double to_calculate(Args args[], Node *list, int size, int level);
void Spaces(int level);
int is_expression_correct(char *str);
double get_value(Args args[], char var, int size, int level);
int is_arg_correct(char* str);
int get_vars(char *str);

