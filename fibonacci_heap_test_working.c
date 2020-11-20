#include"fibonacci_heap_utils.h"

int main()
{
	/*HEAP * my_heap;

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
	d1->parent = n;
	(my_heap->n)++;

	NODE * d2 = create_dummy_node(26);
	d2->mark = 'T';
	(n->child)->child = d2;
	d2->parent = (n->child);
	(my_heap->n)++;

	NODE * d3 = create_dummy_node(46);
	d3->parent = (n->child);
	(n->child->child)->right = d3;
	d3->left =  (n->child->child);
	(n->child->child)->left = d3;
	d3->right = (n->child->child);
	(my_heap->n)++;

	NODE * d4 = create_dummy_node(35);
	n->child->child->child = d4;
	d4->parent = n->child->child;
	(my_heap->n)++;

	/*NODE * m = find_node(my_heap->min , 49);
	if(m == NULL)
	{
		printf("node not found \n");
	}
	m->key = 15;
	printf("%d\n",m->key );
	printf("%d\n",m->parent->key);*/

	/*print_heap(my_heap->min);
	printf("\n");

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

	HEAP * my_heap;

	my_heap = make_fib_heap();

	insert(my_heap,7);

	insert(my_heap,23);

	insert(my_heap,21);

	insert(my_heap,3);

	insert(my_heap,17);

	insert(my_heap,24);

	printf("Calling find_node on node of val 3\n");
	NODE * n = find_node(my_heap->min,3);
	if( n == NULL )
	{
		printf(" Node not found \n ");
	}else{

		printf(" Node found ! \n");
	}

	NODE * d1 = create_dummy_node(18);
	d1->mark = 'T';
	n->child = d1;
	n->degree+=1;
	d1->parent = n;
	(my_heap->n)++;

	NODE * d2 = create_dummy_node(39);
	d2->mark = 'T';
	(n->child)->child = d2;
	d2->parent = (n->child);
	d2->parent->degree+=1;
	(my_heap->n)++;

	NODE * d3 = create_dummy_node(52);
	d3->parent = n;
	n->degree+=1;
	(n->child)->right = d3;
	d3->left =  (n->child);
	(n->child)->left = d3;
	d3->right = (n->child);
	(my_heap->n)++;

	NODE * d4 = create_dummy_node(38);
	d4->parent = n;
	n->degree+=1;
	(n->child->right)->right = d4;
	d4->left =  (n->child->right);
	(n->child)->left = d4;
	d4->right = (n->child);
	(my_heap->n)++;

	NODE * d5 = create_dummy_node(41);
	d5->parent = n->child->right->right;
	n->child->right->right->degree += 1;
	n->child->right->right->child = d5;
	(my_heap->n)++;

 	printf("Calling find_node on node of val 17\n");
	n = find_node(my_heap->min,17);
	if( n == NULL )
	{
		printf(" Node not found \n ");
	}else{

		printf(" Node found ! \n");
	}

	NODE * d6 = create_dummy_node(30);
	n->child = d6;
	n->degree+=1;
	d6->parent = n;
	(my_heap->n)++;

	printf("Calling find_node on node of val 24\n");
	n = find_node(my_heap->min,24);
	if( n == NULL )
	{
		printf(" Node not found \n ");
	}else{

		printf(" Node found ! \n");
	}

	NODE * d7 = create_dummy_node(26);
	d7->mark = 'T';
	n->child = d7;
	n->degree+=1;
	d7->parent = n;
	(my_heap->n)++;

	NODE * d8 = create_dummy_node(35);
	(n->child)->child = d8;
	d8->parent = (n->child);
	d8->parent->degree+=1;
	(my_heap->n)++;

	NODE * d9 = create_dummy_node(46);
	d9->parent = n;
	n->degree+=1;
	(n->child)->right = d9;
	d9->left =  (n->child);
	(n->child)->left = d9;
	d9->right = (n->child);
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

	printf("extract min done \n");

	print_heap(my_heap->min);

	printf("Calling decrease key on node 46 \n");
	decrease_key(my_heap,46,15);

	//printf("Printing mark of node of val 24 : %c\n",n->child->mark);

	print_heap(my_heap->min);

	printf("minimum value is : %d\n",my_heap->min->key);	

	printf("Calling decrease key on node 35 \n");
	decrease_key(my_heap,35,5);

	print_heap(my_heap->min);
	
    return 0;

}