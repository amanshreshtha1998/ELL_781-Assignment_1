#include<stdio.h>
#include<stdlib.h>

typedef struct node
{

	struct node * left;
	struct node * right;
	struct node * child;
	struct node * parent;

	int key;	
	int degree;
	int mark;  // mark = 0 is false , mark = 1 is true

}NODE;


typedef struct heap
{
	NODE * min; // pointer to the minimum value node in the heap

	int n;  // number of nodes in the heap
}HEAP;


HEAP * make_fib_heap()
{
	printf("Making a new fibonacci heap !\n");

	HEAP * H;

	H = malloc(sizeof(HEAP));

	H->min = NULL;

	H->n = 0;

	return H;
}


void insert( HEAP * H , int val )  // insert a new node in the fib_heap with value = val
{
	NODE * new_node;
	new_node = malloc(sizeof(NODE));

	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;

	new_node->key = val;
	new_node->degree = 0;
	new_node->mark = 0;  


	if( (H->min) == NULL )
	{
		H->min = new_node;

		printf("Adding the first node ( val = %d ) to an empty fibonacci heap !\n",val);

		(H->n)++;
		return;
	}

	
	( ( H->min ) -> left ) -> right = new_node;

	new_node->right = H->min;

	new_node->left = (H->min)->left;

    (H->min)->left = new_node;


    printf("Adding a new node ( val = %d ) to the fibonacci heap !\n",val);
    (H->n)++;


    if( (new_node->key) < (H->min)->key )
    {
    	H->min = new_node;
    }

    return;
}


NODE * find_min( HEAP * H )
{
	if( H->min == NULL )
	{
		printf("The fibonacci heap is empty, cannot get the minimum !\n");
		return (NODE *)NULL;
	}

	printf("Returning the minimum node !\n");
	return H->min;
}







