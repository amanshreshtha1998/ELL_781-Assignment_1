#include"fibonacci_heap_utils.h"

int main()
{
	HEAP * my_heap;

	my_heap = make_fib_heap();

	insert(my_heap,10);

	insert(my_heap,30);

	insert(my_heap,5);

	insert(my_heap,20);

	NODE * min_node;

	min_node = find_min(my_heap);
	printf("Minimum vaue in the heap is: %d\n",min_node->key);

	return 0;
}