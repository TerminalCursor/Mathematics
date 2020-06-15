#include "Polynomial.h"

Polynomial* make_polynomial(int degree) {
	Polynomial* polynomial = malloc(sizeof(Polynomial));
	polynomial->degree = degree;
	polynomial->coefficients = (double*)calloc(degree+1, sizeof(double));
	return polynomial;
}

void free_polynomial(Polynomial* polynomial) {
	free(polynomial->coefficients);
	free(polynomial);
}

Polynomial* clone_polynomial(Polynomial* source) {
	Polynomial* destination = make_polynomial(source->degree);
	for(int i = 0; i <= source->degree; i++)
		destination->coefficients[i] = source->coefficients[i];
	return destination;
}

void print_polynomial(Polynomial* polynomial) {
	for(int i = 0; i <= polynomial->degree; i++)
		printf("%5.2f\n", polynomial->coefficients[i]);
	printf("\n");
}

Polynomial* mp_multiply(Matrix* A, Polynomial* x) {
	Polynomial* result = make_polynomial(A->n_rows - 1);
	if(A->n_columns == x->degree + 1) {
		for(int row = 0; row < A->n_rows; row++) {
			for(int column = 0; column <= x->degree+1; column++)
				result->coefficients[row] += A->data[row][column] * x->coefficients[column];
		}
	}
	return result;
}

Polynomial* polynomial_product(Polynomial* p1, Polynomial* p2) {
	Polynomial* result = make_polynomial(p1->degree + p2->degree);
	for(int i = 0; i <= p1->degree; i++) {
		for(int j = 0; j <= p2->degree; j++)
			result->coefficients[i+j] += p1->coefficients[i] * p2->coefficients[j];
	}
	return result;
}

double polynomial_inner_product(Polynomial* p1, Polynomial* p2) {
	Polynomial* full_polynomial = polynomial_product(p1, p2);
	Polynomial* full_polynomial_expanded = make_polynomial(full_polynomial->degree + 1);
	for(int i = 0; i <= full_polynomial->degree + 1; i++)
		full_polynomial_expanded->coefficients[i] = full_polynomial->coefficients[i];

	Matrix* integration_matrix = make_matrix(full_polynomial_expanded->degree + 1,full_polynomial_expanded->degree + 1);
	for(int row = 1; row < integration_matrix->n_rows; row++) {
		int col = row - 1;
		double value = 1.0 / ((double) row);
		integration_matrix->data[row][col] = value;
	}

	Polynomial* integrated_polynomial = mp_multiply(integration_matrix, full_polynomial_expanded);
	double inner_product = apply_x(integrated_polynomial, 1.0f) - apply_x(integrated_polynomial, -1.0f);

	free_matrix(integration_matrix);
	free_polynomial(full_polynomial);
	free_polynomial(full_polynomial_expanded);
	free_polynomial(integrated_polynomial);

	return inner_product;
}

double apply_x(Polynomial* P, double x) {
	double ret_val = 0.0;
	for(int i = 0; i <= P->degree; i++)
		ret_val += d_pow(x, i) * P->coefficients[i];
	return ret_val;
}

Polynomial* polynomial_normalized(Polynomial* P) {
	Polynomial* norm = clone_polynomial(P);
	double scale_factor = square_root(polynomial_inner_product(norm, norm));
	for(int deg = 0; deg <= norm->degree; deg++)
		norm->coefficients[deg] /= scale_factor;
	return norm;
}

Polynomial* polynomial_projection_e(Polynomial* vec, Polynomial* proj_vec) {
	Polynomial* norm_proj_vec = polynomial_normalized(proj_vec);
	Polynomial* res_polynomial = clone_polynomial(norm_proj_vec);
	double inner_product = polynomial_inner_product(vec, norm_proj_vec);
	for(int deg = 0; deg <= norm_proj_vec->degree; deg++)
		res_polynomial->coefficients[deg] *= inner_product;
	free_polynomial(norm_proj_vec);
	return res_polynomial;
}
