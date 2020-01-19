/**
 * @file ex8.c
 * @author Philip R. Simonson
 * @date 01/18/2020
 * @brief Simple example showing file opening and error checking.
 **********************************************************************
 */

#include <stdio.h>
#include "file.h"

int main()
{
	file_t *f;
	int c;

	f = open_file("ex1.c", "rt");
	if(get_error_file() != FILE_ERROR_OKAY)
		return 1;
	while((c = getc_file(f)) != EOF)
		putchar(c);
	if(get_error_file() != FILE_ERROR_OKAY)
		return 1;
	close_file(f);
	return 0;
}
