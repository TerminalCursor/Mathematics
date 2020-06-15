#include "Crypto.h"

int F(int data, int key) {
	return data + key + 7;
}

void swap_two(int* parts) {
	parts[0] ^= parts[1];
	parts[1] ^= parts[0];
	parts[0] ^= parts[1];
}

int* reverse_list(int len, int* list) {
	int* rev_list = malloc(len*sizeof(int));
	for(int i = 0; i < len; i++)
		rev_list[i] = list[len-i-1];
	return rev_list;
}

long Fiestel(int keys, long data, int* key, int (*fptr)(int,int)) {
	long size = 2 * sizeof(data);
	long base_off = l_pow(2, size) - 1;
	int parts[] = {(data & (base_off << size)) >> size, data & base_off};
	int temp;
	for(int rounds = 0; rounds < keys; rounds++) {
		temp = parts[0];
		parts[0] = parts[1];
		parts[1] = temp ^ fptr(parts[1], key[rounds]);
	}
	swap_two(parts);
	return (parts[0] << size) + parts[1];
}

long l_mod_p(long base, long exp, long m) {
	long res = 1;
	for(long i = 0; i < exp; i++) {
		res *= base;
		res %= m;
	}
	return res;
}

long l_mod_p(long base, long exp, long m);
