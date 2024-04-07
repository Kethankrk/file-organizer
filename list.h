typedef struct Node {
    char *name;
    struct Node * next;
} node;

node *create_node(char *name);