/**
 * @file ex2.c
 * @author Philip R. Simonson
 * @date 01/10/2019
 * @brief Simple example showing how to utilise my universal stack.
 **********************************************************************
 * @details Simple example showing how to use my universal stack
 * (ustack).
 */

#include <stdio.h>
#include <stdlib.h>
#include "ustack.h"

/* Free data for stack.
 */
void free_data(void *data)
{
	free(data);
}
/* Program for showing usage of ustack.
 */
int main()
{
	ustack_t *stack;
	int *tmp, i;

	stack = init_stack();
	if(stack == NULL) return 1;
	for(i = 0; i < 10; i++) {
		int *a = (int*)malloc(sizeof(int));
		if(a == NULL) continue;
		*a = i;
		push_stack(stack, a);
	}
	while(peek_stack(stack) != NULL) {
		tmp = (int*)pop_stack(stack);
		printf("%d%s", *tmp, (tmp != NULL ? " " : "\n"));
	}
	free_stack(stack, free_data);
	putchar('\n');
	return 0;
}
