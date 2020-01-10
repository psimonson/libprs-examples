/**
 * @file ex1.c
 * @author Philip R. Simonson
 * @date 01/09/2019
 * @brief Simple universal dynamically linked list example.
 *********************************************************************
 * @details Very simple usage of my universal linked list (ulist).
 */

#ifndef _WIN32
#define _GNU_SOURCE
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ulist.h"
#include "unused.h"

/* data structure for ULIST */
struct data {
	char *s;
	int len;
};
/* Create data for history list.
 */
struct data *create_data(const char *s)
{
	struct data *data;
	data = (struct data *)malloc(sizeof(struct data));
	if(data == NULL) return NULL;
	data->s = (char *)strdup(s);
	if(data->s == NULL) { free(data); return NULL; }
	data->len = strlen(s);
	return data;
}
/* Destroy data for history list.
 */
void destroy_data(void *data)
{
	const struct data *p = (const struct data *)data;
	free(p->s);
}
/* Split into tokens, from given string.
 */
char *const *split_string(char *s)
{
#define MAXTOKENS 100
	static char *tokens[MAXTOKENS];
	char *tmp;
	int i;
	/* split tokens and store addresses */
	tmp = strtok(s, " \r\n");
	for(i = 0; i < 100 && tmp != NULL; i++) {
		tokens[i] = tmp;
		tmp = strtok(NULL, " \r\n");
	}
	tokens[i] = NULL; /* null terminate tokens */
	return (char *const *)tokens;
#undef MAXTOKENS
}
/* Program to test my get input.
 */
int main()
{
	char buf[512], name[128];
	char *const *args;
	char *const *p;
	ulist_t *history;
	ulist_t *tmp;
	int i;

	/* create initial history list */
	history = create_ulist();
	if(history == NULL) {
		perror_ulist();
		return 1;
	}
	if(fgets(buf, 511, stdin) == NULL) exit(1);
	args = split_string(buf);
	/* add history to ulist */
	for(i = 0, p = args; *p != NULL; p++, i++) {
		struct data *data;
		data = create_data(*p);
		if(data == NULL) continue;
		snprintf(name, 128, "history_%d", i);
		if(!i)
			set_attr_ulist(history, name, data);
		else
			add_ulist(history, name, data);
	}
	/* print history from ulist (history) */
	for(tmp = history; tmp != NULL; tmp = get_next_ulist(tmp)) {
		printf("Command: %s\nLength: %d\n",
			(const char *)((struct data *)get_data_ulist(tmp))->s,
			(const int)((struct data *)get_data_ulist(tmp))->len);
	}
	destroy_ulist(&history, destroy_data, 1);
	return 0;
}
