/**
 * @file ex9.c
 * @author Philip R. Simonson
 * @date 01/18/2020
 * @brief Simple example showing off my universal queue data structure.
 **********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "uqueue.h"

/* Program to test uqueue.
 */
int main()
{
	uqueue_data_t *tmp;
	uqueue_t *queue;
	int i;

	srand(time(NULL));
	queue = create_uqueue();
	for(i = 0; i < 10; i++) {
		char *p = (char*)malloc(sizeof(char));
		if(p == NULL) continue;
		*p = (char)rand()%255+1;
		if(!add_uqueue(queue, i, p))
			printf("Added element %d\n", i);
	}
	for(tmp = get_start_uqueue(queue); tmp != NULL;
			tmp = get_next_uqueue(queue)) {
		if(tmp != NULL) {
			printf("ID [%u]: %c\n",
				get_id_uqueue(tmp),
				*(char*)get_data_uqueue(tmp));
		}
	}
	destroy_uqueue(&queue, NULL);
	return 0;
}
