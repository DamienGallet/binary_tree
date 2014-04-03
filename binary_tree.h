#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#define NONE 0
#define LEFT 11
#define RIGHT 12

#define RED 1
#define BLACK 2

/**	------------------ BINARY TREE ------------------------
 *	Implements a straightforward efficient data structure
 *				based on a red-black tree
 *	Weaknesses : the structure isn't enough generic (at the
 *	moment), you can only change the type of satellite data by using
 *					typedef just below
 */

typedef uint64_t* satellite_type;
typedef uint64_t key_type;

typedef struct nodeStruct {
	struct nodeStruct *left;
	struct nodeStruct *right;
	struct nodeStruct *father;
	key_type key;
	satellite_type * content;
	int nodeColor;
} node;

typedef struct binary_tree {
	int size;
	node * root;
} binary_tree;


node * find (node * current_node, key_type key);
node * find_in_tree ( key_type key, binary_tree * tree );

int is_leaf(node * current_node);
int is_root(node * current_node);

int add_node (key_type key, satellite_type * content, binary_tree * tree);
int balance(node * currentNode, binary_tree * tree);

int find_brother (node * currentNode, node ** brother);
int find_position (node * currentNode);
int update_father (node * nodeToUpdate, node * oldSon, node * newSon);

int left_rotation(node * root, node * rootFather, binary_tree * tree);
int right_rotation(node * root, node * rootFather, binary_tree * tree);

void delete_tree(binary_tree * tree);
void delete_node(node * currentNode, binary_tree * tree);

void display_tree(binary_tree * tree);
void display_node(node * currentNode, unsigned int niveau);

void tree_initialization(binary_tree * tree);


#endif
