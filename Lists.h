#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int length;
	int* data;
} List;

List* make_list(int);

List* fill_list(int, int*);

void free_list(List*);

int* i_extend_list(int, int*);

int* i_append_to_list(int, int*, int);

#endif
