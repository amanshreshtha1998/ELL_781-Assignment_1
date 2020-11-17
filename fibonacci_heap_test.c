#include"fibonacci_heap_utils.h"

int main()
{
	HEAP * my_heap;

	my_heap = make_fib_heap();

	insert(my_heap , 7);

	insert(my_heap , 18);

	insert(my_heap , 38);

	print_heap(my_heap);

	NODE * dummy = create_dummy_node(24);

	NODE * node = find_node(my_heap->min , 7 );
	printf("%d\n",node->key);

	node->child = dummy;
	dummy->parent = node;

	decrease_key(my_heap , 24 , 6);

	print_heap(my_heap);

	return 0;
}