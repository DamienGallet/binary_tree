#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "binary_tree.h"

#define NONE 0
#define RED 1
#define BLACK 2

/*------ BINARY_TREE ------
 *
 *
 * 
 * */

node * find (node * current_node, key_type key)
{
	if(current_node==NULL)
		return NULL;

	if(key<current_node->key && current_node->left!=NULL)
		return find(current_node->left, key);
	else if(key>current_node->key && current_node->right!=NULL)
		return find(current_node->right, key);
		
	//If the current is the good one, 
	//OR the current node has not a child at the good place
	return current_node;
}


void tree_initialization(binary_tree * tree)
{
	tree->root = NULL;
	tree->size = 0;
}


node * find_in_tree ( key_type key, binary_tree * tree )
{
	node * foundItem = find(tree->root, key);
	if(foundItem->key == key)
		return foundItem;
	else
		return NULL;
}

int is_leaf(node * current_node)
{
	if(current_node->left == NULL && current_node->right)
		return 1;
	else
		return 0;
}

int is_root(node * current_node)
{
	if(current_node->father==NULL)
		return 1;
	else
		return 0;
}

int add_node (key_type key, satellite_type * content, binary_tree * tree)
// When we add a new node, it's necessarily a leaf, so per convention
// a red node, only if it's the root : so the new node becomes the root
{	
	node * nodeFound = find(tree->root,key);
	node * newNode;								//Check that the variables are declared at the begining of the function

	if(nodeFound!=NULL && nodeFound->key==key)
	//if the node already exists in the tree
		return 0;

	newNode= (node *)malloc(sizeof(node));
	newNode->key = key;
	newNode->content = content;

	newNode->left = NULL;
	newNode->right = NULL;
	newNode->father = nodeFound;
	newNode->nodeColor = RED;
	
	tree->size++;
	if(tree->root==NULL)
	{
		newNode->nodeColor = BLACK;
		tree->root = newNode;
	} else {
		if(key<nodeFound->key)
			nodeFound->left = newNode;
		else if(key>nodeFound->key)
			nodeFound->right = newNode;
		balance(newNode, tree);
	}
	return 1;
}

int balance(node * currentNode, binary_tree * tree)
{
	/*	we have to balance
	* 	if the the currentNode and his father are both RED 
	* */
	node * uncle;
	while(currentNode->father!=NULL && currentNode->father->nodeColor==RED)
	//In this case we are sure that the father isn't the root
	{
		
		//printf("Entree boucle %d\n", currentNode->key);
		switch(find_brother(currentNode->father,&uncle))
		{
			case RIGHT:
			//If our father is the left son of our grand-father
				if((uncle)->nodeColor==RED)
				{
					//printf("R1 %d\n",currentNode->key);
					currentNode->father->nodeColor = BLACK;
					(uncle)->nodeColor = BLACK;
					currentNode->father->father->nodeColor = RED;
					currentNode = currentNode->father->father;
				} else {
					if(find_position(currentNode)==RIGHT) {
						//printf("R2A %d\n",currentNode->key);
						currentNode = currentNode->father;
						left_rotation(currentNode, currentNode->father->father->father,tree);
					}
					//printf("R2B %d\n",currentNode->key);
					currentNode->father->nodeColor = BLACK;
					currentNode->father->father->nodeColor = RED;
					right_rotation(currentNode->father->father, currentNode->father->father->father,tree);
				}
				break;

			case LEFT:
				if((uncle)->nodeColor==RED)
				{
					//printf("L1 %d\n",currentNode->key);
					currentNode->father->nodeColor = BLACK;
					(uncle)->nodeColor = BLACK;
					currentNode->father->father->nodeColor = RED;
					currentNode = currentNode->father->father;
				} else {
					if(find_position(currentNode)==LEFT) {	//
						//printf("L1A %d\n",currentNode->key);
						currentNode = currentNode->father;
						right_rotation(currentNode, currentNode->father->father->father,tree);	//
					}
					//printf("L1B %d\n",currentNode->key);
					currentNode->father->nodeColor = BLACK;
					currentNode->father->father->nodeColor = RED;
					left_rotation(currentNode->father->father, currentNode->father->father->father,tree); //
					
				}
				break;

			default:
				currentNode->father->nodeColor = BLACK;
				currentNode->father->father->nodeColor = RED;
				if(find_position(currentNode->father)==LEFT)
					right_rotation(currentNode->father->father,currentNode->father->father->father,tree);
				else
					left_rotation(currentNode->father->father,currentNode->father->father->father,tree);
				break;
		}
		//display_tree(tree);
		//printf("End disp inter\n");
		
	}
	tree->root->nodeColor = BLACK;
	return 1;
}

int find_brother (node * currentNode, node ** ptBrother)
/*	if our node has a father, we find his brother
*	else, return NONE, else return the position of the brother
* */
{
	if(currentNode->father!=NULL)
	{
		if(currentNode->father->left == currentNode)
		{
			*ptBrother = currentNode->father->right;
			if(*ptBrother==NULL)
				return NONE;
			return RIGHT;
		} else {
			*ptBrother = currentNode->father->left;
			if(*ptBrother==NULL)
				return NONE;
			return LEFT;
		}
	}
	return NONE;
}

int find_position (node * currentNode)
{
	if(currentNode->father!=NULL)
	{
		if(currentNode->father->left == currentNode)
			return LEFT;
		else
			return RIGHT;
	}
	return NONE;
}


int left_rotation(node * root, node * rootFather, binary_tree * tree)
{

	node * right_son = root->right;
	if(tree->root==root)
		tree->root=right_son;

	update_father(rootFather, root,right_son); 
	root->right = right_son->left;
	right_son->father = rootFather;
	right_son->left = root;

	root->father = right_son;
	

	return 1;
}

int right_rotation(node * root, node * rootFather, binary_tree * tree)
{
	node * left_son = root->left;

	if(tree->root==root)
		tree->root=left_son;

	update_father(rootFather, root,left_son); 
	//the old left son's right son become the left son of the old root
	root->left = left_son->right;
	//the old left son becomes the father of the old root
	left_son->right = root;
	left_son->father = rootFather;
	//the old root becomes the right son of the old left son
	root->father = left_son;
	

	return 1;
}

int update_father (node * nodeToUpdate, node * oldSon, node * newSon)
{
	if(nodeToUpdate==NULL)
		return NONE;
	switch(find_position(oldSon))
	{
	case RIGHT:
		nodeToUpdate->right = newSon;
		return RIGHT;
		break;
	case LEFT:
		nodeToUpdate->left = newSon;
		return LEFT;
		break;
	default:
		return NONE;
	}

}

void delete_tree(binary_tree * tree)
{
	delete_node(tree->root, tree);
}

void delete_node(node * currentNode, binary_tree * tree)
{
	if(currentNode->right!=NULL)
		delete_node(currentNode->right, tree);
	if(currentNode->left!=NULL)
		delete_node(currentNode->left, tree);

	tree->size--;
	free(currentNode);
}

void display_tree(binary_tree * tree)
{
	display_node(tree->root,0);
}

void display_node(node * currentNode, unsigned int niveau)
{
	printf("Noeud actuel : %d, couleur : %d, niveau %d\n",currentNode->key,currentNode->nodeColor, niveau);
	if(currentNode->right!=NULL&&niveau<15)
	{
		printf("lv %d Noeud droit | \n",niveau);
		display_node(currentNode->right, ++niveau);
		niveau--;
	}
	if(currentNode->left!=NULL&&niveau<15)
	{
		printf("lv %d Noeud gauche | \n",niveau);
		display_node(currentNode->left, ++niveau);
		niveau--;
	}
	
}
