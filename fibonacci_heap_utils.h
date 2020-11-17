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


HEAP * make_fib_heap();
void insert( HEAP * H , int val );
NODE * find_min( HEAP * H );
void print_heap(HEAP * H);
NODE * find_node( NODE * H_min , int node_val );
void decrease_key( HEAP * H , int curr_val , int dec_val );
void CUT( HEAP * H , NODE * x , NODE * y );
void CASCADING_CUT( HEAP * H , NODE * y );

// remove this function 
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

void print_heap(HEAP * H)
{
	NODE * p = H->min;

	if( p == NULL )
	{
		printf("The heap is empty !\n");
		return;
	}

	// printing the root nodes

	printf(" %d ",p->key);

	p = p->right;

	while( p != H->min )
	{
		printf("--> %d ",p->key);
		
		p = p->right;
	}

	printf("\n");

	printf("There are total %d elements in the fibonacci heap\n",H->n);

}

NODE * find_node( NODE * H_min , int node_val )
// returns the pointer to the node having value as node_val
{
	NODE * curr_node = H_min;

	curr_node->C = 'Y';

	if( curr_node->key == node_val )
	{
		curr_node->C = 'N';
		return curr_node;
	}

	NODE * x = (NODE*)NULL;

	if( curr_node->child != NULL )
	{
		x = find_node(curr_node->child,node_val);
	}

	if( ( curr_node->right )->C != 'Y' )
	{
		x = find_node(curr_node->right,node_val);
	}

	curr_node->C = 'N';

	return x;

}

void decrease_key( HEAP * H , int curr_val , int dec_val )
{
	NODE * p = H->min;

	if( p == NULL)
	{
		printf("Error ! , The given heap is empty. \n");
		return;
	}

	NODE * found_node = NULL;
	found_node = find_node(p , curr_val);

	if( found_node == NULL )
	{
		printf(" Node with given value not present in the heap ! \n");
		return;
	}

	if( found_node->key < dec_val )
	{
		printf("Error ! , New key is greater than the current key ! \n");
		return;
	}

	found_node->key = dec_val;

	
	NODE * parent = found_node->parent;

	if( parent != NULL && found_node->key < parent->key )
	{
		CUT( H , found_node , parent );
		CASCADING_CUT( H , parent );
	}

	if( found_node->key < p->key )
	{
		H->min = found_node; 
	} 

	return;
}

void CUT( HEAP * H , NODE * x , NODE * y )
{

	// remove x from child list of y
	if( x == x-> right )  // x is the only child of y
	{
		y->child = NULL; // now y has no children
	}
	else{
		
		y->child = x->right;

		( x->left )->right = x->right;
		( x->right )->left = x->left;
	}

	x->right = x;
	x->left = x;

	(y->degree)--;

	// add x to the root list

	( ( H->min ) -> left ) -> right = x;

	x->right = H->min;

	x->left = (H->min)->left;

    (H->min)->left = x;

	x->parent = NULL;
	x->mark = 'F';
}

void CASCADING_CUT( HEAP * H , NODE * y )
{
	NODE * z = y->parent;

	if( z != NULL )
	{
		if( y->mark == 'F' )
		{
			y->mark = 'T';
		}
		else{

			CUT( H , y , z );
			CASCADING_CUT( H , z );
		}
	}

}
