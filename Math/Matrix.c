#include "Matrix.h"

// Allocate Memory for Matrix
Matrix* make_matrix(int rows, int columns) {
	Matrix* matrix = malloc(sizeof(Matrix));
	matrix->n_rows = rows;
	matrix->n_columns = columns;
	matrix->data = (double**)malloc(sizeof(double*) * rows);
	for(int row = 0; row < rows; row++)
		matrix->data[row] = (double*)calloc(columns, sizeof(double));
	return matrix;
}

// Deallocate Memory for Matrix
void free_matrix(Matrix* matrix) {
	for(int row = 0; row < matrix->n_rows; row++)
		free(matrix->data[row]);
	free(matrix->data);
	free(matrix);
}

// Clone a matrix to a new matrix object
Matrix* clone_matrix(Matrix* matrix) {
	Matrix* clone = make_matrix(matrix->n_rows, matrix->n_columns);
	for(int row = 0; row < matrix->n_rows; row++)
		for(int column = 0; column < matrix->n_columns; column++)
			clone->data[row][column] = matrix->data[row][column];
	return clone;
}

// Fill a matrix with data from double array
Matrix* fill_matrix(double* data, int rows, int columns) {
	Matrix* matrix = make_matrix(rows, columns);
	for(int row = 0; row < rows; row++)
		for(int column = 0; column < columns; column++)
			matrix->data[row][column] = data[row*columns + column];
	return matrix;
}

// Print out the contents of a matrix
void print_matrix(Matrix* matrix) {
	for(int row = 0; row < matrix->n_rows; row++) {
		for(int column = 0; column < matrix->n_columns; column++) {
			printf("%5.2f ", matrix->data[row][column]);
		}
		printf("\n");
	}
	printf("\n");
}

// ELEMENTARY ROW OPERATIONS
void swap_rows(Matrix* matrix, int rowA, int rowB) {
	for(int column = 0; column < matrix->n_columns; column++) {
		double c = matrix->data[rowA][column];
		matrix->data[rowA][column] = matrix->data[rowB][column];
		matrix->data[rowB][column] = c;
	}
}
void scale_row(Matrix* matrix, int row, double scale_factor) {
	for(int column = 0; column < matrix->n_columns; column++)
		matrix->data[row][column] *= scale_factor;
}
void add_scalar_multiple(Matrix* matrix, int rowin, int rowout, double scale_factor) {
	for(int column = 0; column < matrix->n_columns; column++)
		matrix->data[rowout][column] += matrix->data[rowin][column] * scale_factor;
}

int leading_column(Matrix* matrix, int row) {
	for(int column = 0; column < matrix->n_columns; column++)
		if(matrix->data[row][column] != 0)
			return column;
	return matrix->n_columns;
}

// "Upper Triangular" matrix
void row_reduce(Matrix* matrix) {
	for(int row = 0; row < matrix->n_rows; row++) {
		int leadingColumn = leading_column(matrix, row);
		if(leadingColumn < matrix->n_columns) {
			if(matrix->data[row][leadingColumn] != 0)
				scale_row(matrix, row, 1/matrix->data[row][leading_column(matrix, row)]);

			for(int followingRow = row + 1; followingRow < matrix->n_rows; followingRow++)
				add_scalar_multiple(matrix, row, followingRow, -matrix->data[followingRow][leadingColumn]);
		}
	}

	int currentRow = 0;
	for(int column = 0; column < matrix->n_columns; column++) {
		if(column < matrix->n_rows) {
			int leadingColumnRow = column;
			int leadingColumn = leading_column(matrix, column);
			for(int row = column; row < matrix->n_rows; row++) {
				if(leading_column(matrix, row) < leadingColumn) {
					leadingColumnRow = row;
					leadingColumn = leading_column(matrix, row);
				}
			}
			swap_rows(matrix, currentRow, leadingColumnRow);
		}
		currentRow++;
	}
}

// "Diagonal" Matrix
void reduce_row(Matrix* m) {
	row_reduce(m);

	for(int row = m->n_rows - 1; row >= 0; row--) {
		int leadingColumn = leading_column(m, row);
		for(int previousRow = 0; previousRow < row; previousRow++)
			add_scalar_multiple(m, row, previousRow, -m->data[previousRow][leadingColumn]);
	}
}

// Get the dimension of the matrix
int get_dimension(Matrix* matrix) {
	int dimension = 0;
	if(matrix->n_rows != 0 && matrix->n_columns != 0) {
		Matrix* rref_matrix = clone_matrix(matrix);
		reduce_row(rref_matrix);
		for(int i = 0; i < rref_matrix->n_rows; i++) {
			if(leading_column(rref_matrix, i) == rref_matrix->n_columns) {
				return dimension;
			}
			dimension += 1;
		}
		free_matrix(rref_matrix);
	}
	return dimension;
}

int is_square(Matrix* matrix) {
	return matrix->n_rows == matrix->n_columns;
}

int is_id(Matrix* matrix) {
	if(is_square(matrix)) {
		for(int i = 0; i < matrix->n_rows; i++) {
			if(matrix->data[i][i] != 1.0)
				return 0;
		}
		return 1;
	}
	return 0;
}

Matrix* matrix_multiply(Matrix* A, Matrix* B) {
	if(A->n_columns == B->n_rows) {
		Matrix* resulting_matrix = make_matrix(A->n_rows, B->n_columns);
		for(int row = 0; row < resulting_matrix->n_rows; row++) {
			for(int column = 0; column < resulting_matrix->n_columns; column++) {
				for(int c = 0; c < A->n_columns; c++) {
					resulting_matrix->data[row][column] += A->data[row][c] * B->data[c][column];
				}
			}
		}
		return resulting_matrix;
	}
	Matrix* null = make_matrix(A->n_rows, B->n_columns);
	return null;
}

// Tr(A^TB)
// (This implementation A and B must be both n by m)
double frobenius_inner_product(Matrix* A, Matrix* B) {
	double inner_product = 0.0f;
	if(A->n_rows == B->n_rows && A->n_columns == B->n_columns) {
		for(int row = 0; row < B->n_rows; row++)
			for(int column = 0; column < B->n_columns; column++)
				inner_product += A->data[row][column]*B->data[row][column];
	}
	return inner_product;
}

Matrix* matrix_normalized(Matrix* matrix) {
	Matrix* m = clone_matrix(matrix);
	double scale_factor = 1.0f/square_root(frobenius_inner_product(m, m));
	for(int row = 0; row < m->n_rows; row++) {
		scale_row(m, row, scale_factor);
	}
	return m;
}

Matrix* mat_proj_e(Matrix* mat, Matrix* proj_mat) {
	Matrix* norm_proj_mat = matrix_normalized(proj_mat);
	double inner_product = frobenius_inner_product(mat, norm_proj_mat);

	for(int row = 0; row < norm_proj_mat->n_rows; row++)
		for(int column = 0; column < norm_proj_mat->n_columns; column++)
			norm_proj_mat->data[row][column] *= inner_product;
	Matrix* res_mat = clone_matrix(norm_proj_mat);
	free_matrix(norm_proj_mat);
	return res_mat;
}

Matrix* transpose(Matrix* mat) {
	Matrix* return_matrix = make_matrix(mat->n_columns, mat->n_rows);
	for(int row = 0; row < mat->n_rows; row++) {
		for(int column = 0; column < mat->n_columns; column++) {
			return_matrix->data[column][row] = mat->data[row][column];
		}
	}
	return return_matrix;
}

Matrix* add(Matrix* A, Matrix* B) {
	Matrix* return_matrix = make_matrix(A->n_rows, B->n_columns);
	if(A->n_rows == B->n_rows && A->n_columns == B->n_columns) {
		for(int row = 0; row < A->n_rows; row++) {
			for(int col = 0; col < B->n_columns; col++) {
				return_matrix->data[row][col] = A->data[row][col] + B->data[row][col];
			}
		}
	}
	return return_matrix;
}

Matrix* sub(Matrix* A, Matrix* B) {
	Matrix* return_matrix = make_matrix(A->n_rows, B->n_columns);
	if(A->n_rows == B->n_rows && A->n_columns == B->n_columns) {
		for(int row = 0; row < A->n_rows; row++) {
			for(int col = 0; col < B->n_columns; col++) {
				return_matrix->data[row][col] = A->data[row][col] - B->data[row][col];
			}
		}
	}
	return return_matrix;
}

Matrix* scale(Matrix* matrix, double scale_factor) {
	Matrix* return_matrix = make_matrix(matrix->n_rows, matrix->n_columns);
	for(int row = 0; row < matrix->n_rows; row++) {
		for(int column = 0; column < matrix->n_columns; column++) {
			return_matrix->data[row][column] = scale_factor * matrix->data[row][column];
		}
	}
	return return_matrix;
}

Matrix* cross(Matrix* A, Matrix* B) {
	Matrix* return_matrix = make_matrix(3, 1);
	if(A->n_rows == B->n_rows && A->n_columns == B->n_columns) {
		if(A->n_rows == 3 && B->n_columns == 1) {
			for(int i = 0; i < 3; i++) {
				return_matrix->data[i][0] = A->data[(i+1)%3][0] * B->data[(i+2)%3][0] - A->data[(i+2)%3][3] * B->data[(i+1)%3][0];
			}
		}
		else if(A->n_rows == 2 && B->n_columns == 1) {
			return_matrix->data[2][0] = A->data[0][0] * B->data[1][0] - A->data[1][0] * B->data[0][0];
		}
	}
	return return_matrix;
}

double dot(Matrix* A, Matrix* B) {
	return frobenius_inner_product(A, B);
}
