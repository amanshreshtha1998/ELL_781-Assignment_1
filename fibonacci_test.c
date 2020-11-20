#include"fibonacci_heap_utils.h"

int main()
{
	HEAP * my_heap;

	my_heap = make_fib_heap();

	insert(my_heap,7);

	insert(my_heap,18);

	insert(my_heap,38);

	printf("Calling find_node on node of val 7\n");
	NODE * n = find_node(my_heap->min,7);
	if( n == NULL )
	{
		printf(" Node not found \n ");
	}else{

		printf(" Node found ! \n");
	}

	NODE * d1 = create_dummy_node(24);
	n->child = d1;
	n->degree+=1;
	d1->parent = n;
	(my_heap->n)++;

	NODE * d2 = create_dummy_node(26);
	d2->mark = 'T';
	(n->child)->child = d2;
	
	d2->parent = (n->child);
	d2->parent->degree+=1;
	(my_heap->n)++;

	NODE * d3 = create_dummy_node(46);
	d3->parent = (n->child);
	d3->parent->degree+=1;
	(n->child->child)->right = d3;
	d3->left =  (n->child->child);
	(n->child->child)->left = d3;
	d3->right = (n->child->child);
	(my_heap->n)++;

	NODE * d4 = create_dummy_node(35);
	n->child->child->child = d4;
	d4->parent = n->child->child;
	d4->parent->degree+=1;
	(my_heap->n)++;

	/*NODE * m = find_node(my_heap->min , 49);
	if(m == NULL)
	{
		printf("node not found \n");
	}
	m->key = 15;
	printf("%d\n",m->key );
	printf("%d\n",m->parent->key);*/

	print_heap(my_heap->min);
	printf("number of nodes in my_heap is %d \n", my_heap->n);
	printf("\n");
	printf ("calling extract_min on H \n");
	ext_min(my_heap);
    return 0;
	/*
	printf("Printing mark of node of val 24 : %c\n",n->child->mark);

	printf("Calling decrease key on node 46 \n");
	decrease_key(my_heap,46,15);

	printf("Printing mark of node of val 24 : %c\n",n->child->mark);

	print_heap(my_heap->min);
	printf("\n");

	printf("minimum value is : %d\n",my_heap->min->key);	

	printf("Calling decrease key on node 35 \n");
	decrease_key(my_heap,35,5);

	printf("minimum value is : %d\n",my_heap->min->key);

	insert(my_heap,6);

	print_heap(my_heap->min);
	printf("\n");

	insert(my_heap,4);

	print_heap(my_heap->min);
	printf("\n");

	printf("minimum value is : %d\n",my_heap->min->key);

	return 0;*/
}