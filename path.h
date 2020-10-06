typedef struct node
{
	char* name;
	struct node* next;
} node_t;

extern node_t* root_node;
extern node_t* curr_node;
extern node_t* prev_node;
extern node_t* temp_node;

void makenode(char*);
void delnode(void);
void freenode(node_t*);
void print_nodes(node_t*, char);
void initpath(void);
void buildpath(char*);
void delpath(node_t*);