typedef struct BinTree{
	char data;
	int left;
	int right;
        int size;
}BinTree;

void Space(int level);
int are_similar(BinTree *bt1, BinTree *bt2, int level, int *is_equal);
int are_mirrored(BinTree *bt1, BinTree *bt2, int level, int *is_symm);
int CreateElem(BinTree *bt, char data, int size, int is_atom);
int CreateTree(BinTree *bt, char* str, int level, int size);
int is_correct(char *str);


