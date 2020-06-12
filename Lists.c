#include "Lists.h"

List* make_list(int length) {
	int* list = malloc(length*sizeof(int));
	List* result = malloc(sizeof(List));
	result->length = length;
	result->data = list;
	return result;
}

List* fill_list(int length, int* list) {
	List* result = make_list(length);
	for(int i = 0; i < length; i++)
		result->data[i] = list[i];
	return result;
}

void free_list(List* list) {
	free(list);
}

int* i_extend_list(int length, int* list) {
	int* result = malloc((length+1)*sizeof(int));
	for(int i = 0; i < length; i++)
		result[i] = list[i];
	result[length] = 0;
	return result;
}

int* i_append_to_list(int length, int* list, int value) {
	int* result = i_extend_list(length, list);
	result[length] = value;
	return result;
}
