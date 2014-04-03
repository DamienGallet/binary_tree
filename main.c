#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "binary_tree.h"

int main(int argc, char *argv[])
{
	binary_tree myTree;
	tree_initialization(&myTree);
	printf("Retour ajout 10 : %d\n\n\n",add_node(10,NULL,&myTree));
	printf("Retour ajout 10B : %d\n\n\n",add_node(10,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 9 : %d\n\n\n\n",add_node(9,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 8 : %d\n\n\n",add_node(8,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 12 : %d\n\n\n",add_node(12,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 6 : %d\n\n\n",add_node(6,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 5 : %d\n\n\n",add_node(5,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 6 : %d\n\n\n",add_node(7,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 4 : %d\n\n\n",add_node(4,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 3 : %d\n\n\n",add_node(3,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 2 : %d\n\n\n",add_node(2,NULL,&myTree));
	display_tree(&myTree);
	printf("Retour ajout 1 : %d\n\n\n",add_node(1,NULL,&myTree));
	display_tree(&myTree);
	
	return 0;
}

