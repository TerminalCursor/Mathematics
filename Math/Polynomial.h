#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Matrix.h"

typedef struct {
	int degree;
	double* coefficients;
} Polynomial;

Polynomial* make_polynomial(int);

void free_polynomial(Polynomial*);

Polynomial* clone_polynomial(Polynomial*);

void print_polynomial(Polynomial*);

Polynomial* mp_multiply(Matrix*, Polynomial*);

Polynomial* polynomial_product(Polynomial*, Polynomial*);

double polynomial_inner_product(Polynomial*, Polynomial*);

double apply_x(Polynomial*, double);

Polynomial* polynomial_normalized(Polynomial*);

Polynomial* polynomial_projection_e(Polynomial*, Polynomial*);

#endif
