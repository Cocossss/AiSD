typedef struct Node {
    void* key;
    int size;
    struct Node* left;
    struct Node* right;
} Node;

int fixsize(Node* tree);
Node* RotateRight(Node* tree, size_t size, int level);
Node* RotateLeft(Node* tree, size_t size, int level);
Node* InsertRoot(Node* tree, void* key, size_t size, int level);
Node* Insert(Node* tree, void* key, size_t size, int level);
void showtree(Node* tree, size_t size);
Node* Join(Node* tree1, Node* tree2);
Node* Remove(Node* tree, size_t size, char* to_delete, int* flag, int level);
void delete_BT(Node* tree);
int GetElements(float* keys, char* keys_ch, char* str, size_t fixtype);
