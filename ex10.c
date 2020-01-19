/**
 * @file ex10.c
 * @author Philip R. Simonson
 * @date 01/18/2020
 * @brief Simple program to test the universal tree.
 ********************************************************************
 * @details This program will try to test every aspect of the utree
 * implementation.
 ********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utree.h"

struct data {
	char name[32];
	int age;
};
/* Create data function.
 */
static struct data *create_data(const char *name, int age)
{
	struct data *data;
	data = (struct data *)malloc(sizeof(struct data));
	if(!data) return NULL;
	strncpy(data->name, name, strlen(name));
	data->age = age;
	return data;
}
/* Destroy data function.
 */
static void destroy_data(void *p)
{
	struct data *data = (struct data*)p;
	if(data != NULL) {
		free(data);
	}
}
/* Print all data in tree.
 */
void print_data_utree(utree_t *leaf)
{
	if(leaf != NULL) {
		printf("utree data [%d]: [%s|%d]\n",
			get_id_utree(leaf),
			((struct data *)get_data_utree(leaf))->name,
			((struct data *)get_data_utree(leaf))->age);
		print_data_utree(get_left_utree(leaf));
		print_data_utree(get_right_utree(leaf));
	}
}
/* Program to test binary tree.
 */
int main()
{
	utree_t *tree = NULL, *leaf = NULL;
	int i;

	srand(time(NULL));
	for(i = 0; i < 10; i++) {
		struct data *p = create_data("hello_moto", i+1);
		if(p == NULL) {
		       printf("Error creating data...\n");
		       continue;
		}
		add_utree(&tree, i, p);
		printf("Added item %d to tree.\n", i);
	}
	print_utree(tree, 0);
	printf("========================================\n");
	print_data_utree(tree);
	printf("========================================\n");
	leaf = search_utree(tree, 5);
	if(leaf != NULL) {
		printf("Data [%d]: %s\n",
			((struct data *)get_data_utree(leaf))->age,
			((struct data *)get_data_utree(leaf))->name);
	}
	leaf = search_utree(tree, 6);
	if(leaf != NULL) {
		printf("Data [%d]: %s\n",
			((struct data *)get_data_utree(leaf))->age,
			((struct data *)get_data_utree(leaf))->name);
	}
	leaf = search_utree(tree, 9);
	if(leaf != NULL) {
		printf("Data [%d]: %s\n",
			((struct data *)get_data_utree(leaf))->age,
			((struct data *)get_data_utree(leaf))->name);
	}
	destroy_utree(&tree, destroy_data);
	return 0;
}
