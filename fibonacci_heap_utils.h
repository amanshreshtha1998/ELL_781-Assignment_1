#include<stdio.h>
#include<stdlib.h>

typedef struct node
{

	// pointers
	struct node * left;
	struct node * right;
	struct node * child;
	struct node * parent;

	// value of the node
	int key;

	// extra information
	int degree;
	char mark;  
	char C;

}NODE;


typedef struct heap
{
	NODE * min; // pointer to the minimum value node in the heap

	int n;  // number of nodes in the heap
}HEAP;


HEAP * make_fib_heap(); // correct
void insert( HEAP * H , int val ); // correct
NODE * find_min( HEAP * H ); // correct

NODE * create_dummy_node(int val)
{
	NODE * new_node;
	new_node = malloc(sizeof(NODE));

	new_node->left = new_node;
	new_node->right = new_node;
	new_node->parent = NULL;
	new_node->child = NULL;

	new_node->key = val;

	new_node->degree = 0;
	new_node->mark = 'F';
	new_node->C = 'N'; 

	return new_node;
}


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
	new_node->mark = 'F';
	new_node->C = 'N';  


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

void print_heap(NODE * H_min)
{
	NODE * ptr = H_min;

	ptr->C = 'Y';

	printf(" %d --> ",ptr->key);

		if( ptr->child != NULL )
		{
			print_heap(ptr->child);
		}

		if( (ptr->right)->C != 'Y' )
		{
			print_heap(ptr->right);
		}

	ptr->C = 'N';

}

NODE * find_node(NODE * H_min , int val)
{
	NODE * ptr = H_min;

	//printf("The value of node is: %d\n",ptr->key);

	ptr->C = 'Y';

	NODE * x = NULL;

	if( ptr->key == val )
	{
		//printf("The found node is: %d\n",ptr->key);
		x = ptr;
		ptr->C = 'N';
		return x;
	}

	if( x == NULL )
	{
		if( ptr->child != NULL )
		{
			x = find_node(ptr->child,val);
		}

		if( (ptr->right)->C != 'Y' && x == NULL )
		{
			x = find_node(ptr->right,val);
		}
	}

	ptr->C = 'N';
	return x;
}

void CUT( NODE* H_min , NODE * x , NODE * y )
{
	if( x == x->right )
	{
		y->child = NULL;
	}

	else{

		y->child = x->right;

		(x->left)->right = x->right;
		(x->right)->left = x->left;

	}

	/*(x->left)->right = x->right;
	(x->right)->left = x->left;

	if(x == y->child)
	{
		y->child = x->right;
	}*/

	y->degree = y->degree-1;

	x->right = x;
	x->left = x;

	(H_min->left)->right = x;
	x->right = H_min;
	x->left = (H_min->left);
	H_min->left = x;

	x->parent = NULL;
	x->mark = 'F';

	printf("Node of value = %d added to the root list\n",x->key);
}

void CASCADING_CUT(NODE * H_min , NODE * y)
{
	NODE* z = y->parent;

	if(z != NULL)
	{
		if(y->mark == 'F')
		{
			y->mark = 'T';
		}
		else{

			CUT(H_min,y,z);
			CASCADING_CUT(H_min,z);
		}
	}
}

void decrease_key(HEAP * H , int curr_val , int dec_val)
{
	NODE * H_min = H->min;

	if(H_min == NULL)
	{
		printf("Error!, The heap is empty\n");
		return;
	}

	NODE * found_node = find_node(H_min , curr_val);

	if( found_node == NULL )
	{
		printf("Error!, Node not found\n");
		return;
	}

	if( found_node->key < dec_val )
	{
		printf("Error!, the new value is greater than previous value.\n");
		return;
	}

	NODE * parent = found_node->parent;

	found_node->key = dec_val;	

	if( parent != NULL && found_node->key < parent->key )
	{
		CUT(H_min , found_node , parent);
		CASCADING_CUT(H_min , parent);
	}

	
	if(found_node->key < H->min->key)
	{
		H->min = found_node;
	}
	return;
}

