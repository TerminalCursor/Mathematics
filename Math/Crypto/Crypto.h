#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdio.h>
#include <stdlib.h>
#include "../General.h"

int F(int data, int key);

void swap_two(int* parts);

int* reverse_list(int len, int* list);

long Fiestel(int keys, long data, int* key, int (*fptr)(int,int));

long l_mod_p(long base, long exp, long m);

#endif
