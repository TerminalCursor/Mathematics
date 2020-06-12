#include <stdio.h>
#include <stdlib.h>
#include "Math/Matrix.h"
#include "Math/Polynomial.h"
#include "Math/General.h"
#include "Math/Crypto/Crypto.h"
#include "Lists.h"

int main() {
	/* Fiestel */
	long leData = 0x30F0E67;
	int leKeys[] = {8, 6, 7};
	int* leKeys1 = reverse_list(3, leKeys);
	int (*fptr)(int, int) = &F;
	printf("0x%08lX\n0x%08lX\n\n", leData, Fiestel(3, Fiestel(3, leData, leKeys, fptr), leKeys1, fptr));
	free(leKeys1);

	/* Diffie Hellman */
	long a = 36, b = 425, p = 997, g = 573;
	long A = l_mod_p(g, a, p);
	long B = l_mod_p(g, b, p);
	long S = l_mod_p(A, b, p);
	printf("Publicly Known:\n	p: % 5li\n	g: % 5li\n	A: % 5li *\n	B: % 5li *\n", p, g, A, B);
	printf("Privately Known:\n	a: % 5li\n	b: % 5li\n Secret: % 5li *\n", a, b, S);
	printf("* indicates a calculated value\n\n");

	/* List Stuff */
	int list_1_data[] = {1, 2, 3, 4};
	List* list = fill_list(4, list_1_data);
	list->data = list_1_data;
	List* list_2 = fill_list(list->length + 1, i_extend_list(4, list->data));
	list_2->data[4] = -5;
	for(int i = 0; i < list_2->length; i++)
		printf("% 2i: % 4i\n", i+1, list_2->data[i]);
	printf("\n");
	free_list(list);
	free_list(list_2);

	/* Matrix Stuff */
	double matrix_1_data[] = {0, 0, 0, 0, 1, 8, 0, 1, 8};
	Matrix* test_m = fill_matrix(matrix_1_data, 3, 3);
	print_matrix(test_m);
	Matrix* test_r = clone_matrix(test_m);
	reduce_row(test_r);
	print_matrix(test_r);
	Matrix* test_n = matrix_normalized(test_r);
	print_matrix(test_n);
	printf("%i\n%i\n\n", get_dimension(test_n), is_id(test_n));
	free_matrix(test_n);
	free_matrix(test_r);
	free_matrix(test_m);

	/* GCD Stuff */
	int a_1 = 26, b_1 = 56;
	printf("gcd(%i, %i): %i\n", a_1, b_1, gcd(a_1, b_1));

	return 0;
}
