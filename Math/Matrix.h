#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "General.h"

typedef struct {
	int n_rows;
	int n_columns;
	double** data;
} Matrix;

Matrix* make_matrix(int, int);

void free_matrix(Matrix*);

Matrix* clone_matrix(Matrix*);

Matrix* fill_matrix(double*, int, int);

void print_matrix(Matrix*);

// ELEMENTARY ROW OPERATIONS
void swap_rows(Matrix*, int, int);
void scale_row(Matrix*, int, double);
void add_scalar_multiple(Matrix*, int, int, double);

int leading_column(Matrix*, int);

void row_reduce(Matrix*);

void reduce_row(Matrix*);

int get_dimension(Matrix*);

int is_square(Matrix*);

int is_id(Matrix*);

Matrix* matrix_multiply(Matrix*, Matrix*);

double frobenius_inner_product(Matrix*, Matrix*);

Matrix* matrix_normalized(Matrix*);

Matrix* mat_proj_e(Matrix*, Matrix*);

Matrix* transpose(Matrix*);

Matrix* add(Matrix*, Matrix*);
Matrix* sub(Matrix*, Matrix*);
Matrix* scale(Matrix*, double);

Matrix* cross(Matrix*, Matrix*);
double dot(Matrix*, Matrix*);

#endif
