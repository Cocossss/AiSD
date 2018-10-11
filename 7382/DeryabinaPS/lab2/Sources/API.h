typedef struct Node{
    union{               // contains operation "-", "+", "/", "*" or an argument
	char operation;
	char var;
    };
    int is_atom;         // = 1, if nide is atom
    struct Node *next;   // next element
    struct  Node *sublist;  // ponter on sublist
} Node;

typedef struct  Args{   // contains argument and its value
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
void delete_list(Node* first, Node* second);
