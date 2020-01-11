/**
 * @file ex7.c
 * @author Philip R. Simonson
 * @date 01/10/2020
 * @brief Showing how to use a data structure with my vector implementation.
 ******************************************************************************
 * @details Just showing off how to use a simple data structure with the
 * vector library, in my P.R.S. library.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

/* Custom data structure for vector. */
struct data {
	char *s;
	int len;
};
/* My hopefully secure string copy function.
 */
int str_copy(char *s, size_t size, const char *t, size_t len)
{
	char *p = (char*)t;
	size_t i;
	for(i = 0; (i < size || --len > 0) && (*s++ = *p++) != 0; i++);
	return i;
}
/* My string duplication function.
 */
char *str_dup(const char *s, const int len)
{
	char *p;
	p = (char*)malloc(sizeof(char)*len);
	if(p == NULL) return NULL;
	str_copy(p, len, s, len);
	return p;
}
/* Creates a data structure.
 */
struct data *create_data(const char *s)
{
	struct data *data;
	const int len = strlen(s);
	data = (struct data *)malloc(sizeof(struct data));
	if(data == NULL) return NULL;
	data->s = str_dup(s, len);
	if(data->s == NULL) { free(data); return NULL; }
	data->len = len;
	return data;
}
/* Destroys a data structure.
 */
void destroy_data(struct data *data)
{
	if(data != NULL) {
		free(data->s);
		free(data);
	}
}
/* Program for showing, how to use data structures with vectors.
 */
int main()
{
	struct data **vec = NULL, **p;
	/* push back data */
	vector_push_back(vec, create_data("Hello world."));
	vector_push_back(vec, create_data("This is a test."));
	vector_push_back(vec, create_data("Welcome to my example."));
	vector_push_back(vec, create_data("The second one for vectors."));
	for(p = vector_begin(vec); p != vector_end(vec); p++)
		printf("Data: %s\nLength: %d\n",
			(const char*)(*p)->s, (const int)(*p)->len);
	for(p = vector_begin(vec); p != vector_end(vec); p++)
		destroy_data((*p));
	vector_free(vec);
	return 0;
}
