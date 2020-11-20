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
	int visited;

}NODE;


typedef struct heap
{
	NODE * min; // pointer to the minimum value node in the heap

	int n;  // number of nodes in the heap
}HEAP;


HEAP * make_fib_heap(); 
// this function delares a new fibonacci heap

void insert( HEAP * H , int val ); 
// insert a new node into the fibonacci heap

NODE * find_min( HEAP * H ); 
// returns the node containing the minimum value in the fibonacci heap 

void print_heap(NODE * H_min);
// prints the fibonacci heap

NODE * find_node(NODE * H_min , int val);
// return the node with the given val

void decrease_key(HEAP * H , int curr_val , int dec_val);
// decrease the value of a node and reconfigure the heap

void CUT( NODE* H_min , NODE * x , NODE * y );
void CASCADING_CUT(NODE * H_min , NODE * y);



// this function is used for adding nodes at positions other than the root list
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
	new_node->visited = 0; 

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
	new_node->visited = 0;  


	if( (H->min) == NULL ) // no node already added to the fibonacci heap
	{
		H->min = new_node;

		printf("Adding the first node ( val = %d ) to an empty fibonacci heap !\n",val);

		(H->n)++;
		return;
	}

	// adding the new node to the root list as the left sibling of the H->min node
	
	( ( H->min ) -> left ) -> right = new_node;

	new_node->right = H->min;

	new_node->left = (H->min)->left;

    (H->min)->left = new_node;


    printf("Adding a new node ( val = %d ) to the fibonacci heap in the root list !\n",val);
    (H->n)++;  // increasing the size by one


    if( (new_node->key) < (H->min)->key )  // if the value of the new node is smaller then make it the minimum
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

	ptr->visited = 1;

	printf(" %d { degree: %d , mark: %c , visited : %d }\n",ptr->key,ptr->degree,ptr->mark,ptr->visited);

		if( ptr->child != NULL )
		{
			printf(" [child of %d] ",ptr->key);
			print_heap(ptr->child);
		}

		if( (ptr->right)->visited != 1 )
		{
			printf(" [right of %d] ",ptr->key);
			print_heap(ptr->right);
		}

	ptr->visited = 0;

}

NODE * find_node(NODE * H_min , int val)
{
	NODE * ptr = H_min;

	//printf("The value of node is: %d\n",ptr->key);

	ptr->visited = 1;

	NODE * x = NULL;

	if( ptr->key == val )
	{
		//printf("The found node is: %d\n",ptr->key);
		x = ptr;
		ptr->visited = 0;
		return x;
	}

	if( x == NULL )
	{
		if( ptr->child != NULL )
		{
			x = find_node(ptr->child,val);
		}

		if( (ptr->right)->visited != 1 && x == NULL )
		{
			x = find_node(ptr->right,val);
		}
	}

	ptr->visited = 0;
	return x;
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


int degree(int n)
{
	int deg=0;
	while(n>0)
	{	
		n=n/2;
		deg++;
	}
	return deg;
}

void link_heaps(HEAP *H, NODE *y , NODE *x)
{  
	(y->left)->right = y->right;
  	(y->right)->left = y->left;
  
  	y->left = y;
  	y->right = y;
  	y->parent = x;

  	if (x->child == NULL)
    	x->child = y;

  	y->right = x->child;
  	y->left = (x->child)->left;
  	((x->child)->left)->right = y;
  	(x->child)->left = y;

  	if (y->key < (x->child)->key)
    	x->child = y;
  	x->degree++;
  	y->mark = 'F';
}

void consolidate (HEAP * H)
{

	int i;
	int dMax,d;

	dMax = degree(H->n);

	NODE * a[dMax], *x,*y,*temp;
	printf("max degree of a node in H is = %d \n", (dMax-1));

 
	for ( i=0 ; i<dMax ; i++)
	{
		a[i]= (NODE *) NULL;
	}

	x = H->min;

	do
	{
		printf ("visiting node (val = %d) \n", x->key);
		
		d = x->degree ;
		printf ("degree of node (val = %d) is (d = %d) \n", x->key, d);
		
		while(a[d]!=NULL && a[d]->key != x->key )
		{
			y = a[d];     
			printf ("found node with same degree(%d) having (val = %d) \n",d, y->key);

			if (x->key > y->key)
			{
				temp = x;  // exchange x and y
				x = y;
				y = temp;
			}

			link_heaps (H,y,x);

			a[d] = (NODE *)NULL;
			d = d+1;
		}
	
		a[d] = x;    //a[d] is node having degree d
		x = x->right;

	}while(x != H->min);

	printf ("visited all nodes in the root list \n");


	H->min = (NODE *)NULL;

	for ( int i=0 ; i<dMax ; i++) 
	{ // checking a[i]
		if (*(a+i) != (NODE *)NULL)
		{ //adding a[i] to the root list
			a[i] -> right = a[i];
			a[i] -> left = a[i];

			if(H->min != (NODE *)NULL)
			{
				( H->min -> left ) -> right = a[i];
				a[i]->right = H->min;
				a[i]->left = (H->min)->left;
				(H->min)->left = a[i];

				printf ("value of H->min node is %d \n", H->min->key);
				
			if( a[i]->key < H->min->key )
				H->min = a[i]; //updating H->min
		}
		else
		{
			H->min = a[i];
			printf ("adding node (val = %d) to root list \n", a[i]->key);
		}

		if( H->min == NULL )
		{
			H->min = a[i];
		}
		else if( a[i]->key < H->min->key )
		{
			H->min = a[i];
		}

	}
}


	return;

}



NODE * ext_min(HEAP * m) {

	int nodesCount = m->n;
	printf("heap is having %d nodes \n", nodesCount);

	NODE *temp, *rgt;

	if( m->min == NULL)
		printf("Error ! Your Heap Is Empty, cannot extarct the minimum.\n");
	else
	{
		NODE *c =NULL;
		//NODE *temp, *rgt;
		temp=  m->min;
		rgt = temp;
		printf("extracted minimum is temp (val = %d)\n",temp->key);
		//adding the child nodes to the root list//
		if( temp->child !=NULL)
		 { 
		  
		            c = temp->child; 
		            do { 
		                rgt = c->right; 

		                ( m->min->left)->right = c; 
		                c->left =  m->min->left;
		                m->min->left = c;
		                c->right = m->min; 
		                printf ("adding node (val = %d) to root list \n", c->key);
		                 
		                //extracting the min value//
		                if (c->key <  m->min->key) 
		                	 m->min = c; 
		                c->parent = NULL; 
		                c = rgt; 
		            } while (rgt != temp->child); 
		    } 

		//extracting the Min Node//
    (temp->right)->left = temp->left; 
    (temp->left)->right = temp->right; 
    printf ("node (val = %d) removed from the heap \n", temp->key);

    m->min = temp->right; 
	if (temp == temp->right && temp->child == NULL) //if min is the only node//
		 m->min = NULL; 
    else { 
    	  m->min = temp->right;  //rearrange the tree//
		  printf ("node (val = %d) is the m->min now \n", m->min->key);
	      consolidate(m); 
	     } 
	nodesCount-=1; 
	m->n = nodesCount;
    printf("heap is having %d nodes \n", nodesCount);
	}

	return temp; 

} 



