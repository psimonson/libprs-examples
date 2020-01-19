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

/* Program for showing usage of ustack.
 */
int main()
{
	ustack_t *stack;
	int i;

	stack = create_ustack();
	if(stack == NULL) return 1;
	for(i = 0; i < 10; i++) {
		int *a = (int*)malloc(sizeof(int));
		if(a == NULL) continue;
		*a = i;
		if(push_ustack(stack, i, a) == 0)
			continue;
		printf("Push element %d to stack.\n", i);
	}
	while(peek_ustack(stack) != NULL) {
		ustack_data_t *tmp = pop_ustack(stack);
		if(tmp != NULL) {
			printf("Data ID [%u]: %d\n",
				get_id_ustack(tmp),
				*(int*)get_data_ustack(tmp));
		}
	}
	destroy_ustack(&stack, NULL);
	return 0;
}
