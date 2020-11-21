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
void consolidate (HEAP * H);
void link_heaps(HEAP *H, NODE *x,NODE *y);
void add_node(NODE *exist, NODE *new);
int degree(int n);
NODE * ext_min(HEAP * m);

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

void consolidate (HEAP * H)
{
//int n = 8;
int i;
int dMax,d;
//NODE *a[dMax], *x,*y,*temp;
dMax = degree(H->n);

//dMax = (int) floor (log(H->n)/log(2));
NODE *a[dMax], *x,*y,*temp;
printf("max degree of a node in H is = %d \n", (dMax-1));

//a[0] = (NODE *) malloc(4 * sizeof(NODE *)); //auxillary array 
for (i=0;i <dMax; i++)
	a[i]= (NODE *) NULL;


x=H->min;

do{
printf ("visiting node (val = %d) \n", x->key);
d=x->degree ;
printf ("degree of node (val = %d) is (d = %d) \n", x->key, d);
while(a[d]!=NULL)
{
y = a[d];     
printf ("found node with same degree(%d) having (val = %d) \n",d, y->key);

if (x->key > y->key)

{temp = x;   /*exchange x and y*/
x = y;
y = temp;
}

link_heaps (H,x,y);

a[d] = (NODE *)NULL;
d = d+1;
}
a[d] = x;    //a[d] is node having degree d
x = x->right;

}while(x != H->min);
printf ("visited all nodes in the root list \n");

H->min = (NODE *)NULL;

for (i=0;i<dMax;i++)
 
{ // checking a[i]
if (*(a+i) != (NODE *)NULL)

{ //adding a[i] to the root list
a[i] -> right = a[i];
a[i] -> left = a[i];

if(H->min == (NODE *)NULL)
{H->min = a[i];
printf ("adding node (val = %d) to root list \n", a[i]->key);}
else
{add_node(H->min, a[i]);}
/*( H->min -> left ) -> right = a[i];
a[i]->right = H->min;
a[i]->left = (H->min)->left;
(H->min)->left = a[i];
*/
printf ("value of H->min node is %d \n", H->min->key);
if((H->min = (NODE *)NULL) || (a[i]->key < H->min->key))
{H->min = a[i]; }//updating H->min
printf ("value of updated H->min node is %d \n", H->min->key);
}//adding a[i] to the root list
}// checking a[i]
return;
}

void link_heaps(HEAP *H, NODE *x , NODE *y)
{   y->right->left = y->left; //removing y from root list
    y->left->right = y->right;
    printf ("node (val = %d) removed from the root list \n", y->key);
    y->parent = x;
    y->left = y;
    y->right =y;

    //making y the child of x
   if(x->child == NULL) 
   {
       x->child = y; 
	   printf ("y(%d) is now child of x(%d) \n",y->key, x->key);
   }
   else
       {add_node(x->child, y);  //look
       printf ("y(%d) is added to child list of x(%d) \n",y->key, x->key);}
    x->degree = x->degree + 1;
    y->mark = 'F';
return ;
}

void add_node(NODE *exist, NODE *new)
{
    (exist -> left ) -> right = new;
    new->right = exist ;
    new->left = exist->left;
    exist->left = new;
	return ;

}

int degree(int n)
{int deg=0;
while(n>0)
{n=n/2;
deg++;}
return deg;
}

NODE * ext_min(HEAP * m) {

	int nodesCount = m->n;
	printf("heap is having %d nodes \n", nodesCount);

	NODE *temp, *rgt;
	if( m->min == NULL)
		printf("Your Heap Is Empty");
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
		                if ( m->min->key  > c->key) 
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
    printf("heap is having %d nodes \n", nodesCount);
	 }
return temp; 
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

