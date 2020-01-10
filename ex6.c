/**
 * @file ex6.c
 * @author Philip R. Simonson
 * @date 01/10/2020
 * @brief Simple example of using my vectors.
 ************************************************************
 * @details Just a small example of using vectors.
 */

#include <stdio.h>
#include "vector.h"

/* Program to show off my vector lib.
 */
int main()
{
	int *vec = NULL, *p;
	unsigned long i;

	/* push back values to vector */
	vector_push_back(vec, 1);
	vector_push_back(vec, 2);
	vector_push_back(vec, 3);
	vector_push_back(vec, 4);
	/* using as a vector */
	printf("Vector form...\n");
	for(p = vector_begin(vec); p != vector_end(vec); p++)
		printf("Integer: %d\n", *p);
	/* or you can display like an array (that's basically what it is) */
	printf("Array form...\n");
	for(i = 0; i < vector_size(vec); i++)
		printf("Integer: %d\n", vec[i]);
	vector_free(vec);
	return 0;
}
