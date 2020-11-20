#include"fibonacci_heap_utils.h"

int main()
{
	HEAP * my_heap;

	my_heap = make_fib_heap();

	printf("Enter number of root list elements.\n");

	int rootNum;

	scanf("%d",&rootNum);

	for(int i=0;i<rootNum;i++)
	{
		int key;

		scanf("%d",&key);

		insert(my_heap,key);
	}

	int non_rootNum;

	printf("Enter number of non-root list elements. \n");

	scanf("%d",&non_rootNum);

	for(int i=0;i<non_rootNum;i++)
	{
		int main_node;
		int CorR;
		int key;
		char mark;

		scanf("%d %d %d %c",&main_node,&CorR,&key,&mark);

		NODE * n = find_node(my_heap->min,main_node);

		if( CorR == 0 )
		{
			NODE * d = create_dummy_node(key);
			d->mark = mark;
			n->child = d;
			n->degree+=1;
			d->parent = n;
			(my_heap->n)++;
		}
		if( CorR == 1 )
		{
			NODE * d = create_dummy_node(key);
			d->parent = n->parent;
			n->parent->degree+=1;

			( n -> left ) -> right = d;
			d->right = n;
			d->left = n->left;
			n->left = d;
			(my_heap->n)++;		
		}

	}

	printf("%d",my_heap->n);

	print_heap(my_heap->min);

	return 0;
}