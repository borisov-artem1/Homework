#include "matrix.h"

// NOTE(stitaevskiy): Place your implementation here
// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE* ptr_filename = fopen(path_file, "r");
    int check_fscanf = 0;
    if (!ptr_filename) {
        return NULL;
    }
    Matrix* print_matrix = (Matrix *)malloc(sizeof(Matrix));
    print_matrix->mat_rows = 0;
    print_matrix->mat_cols = 0;
    check_fscanf = fscanf(ptr_filename, "%zu%zu", &print_matrix->mat_rows, &print_matrix->mat_cols);
    if (check_fscanf != COUNT_ROWS_AND_COLS) {
        puts("error: can't scan rows or cols");
        free(print_matrix);
        fclose(ptr_filename);
        return NULL;
    }
    print_matrix->value = (double **)malloc(print_matrix->mat_rows * sizeof(double*));
    if (print_matrix->mat_rows == 0 || print_matrix->mat_cols == 0) {
        puts("error: rows or cols equal to zero");
        free(print_matrix->value);
        free(print_matrix);
        fclose(ptr_filename);
        return NULL;
    }
    for (size_t i = 0; i < print_matrix->mat_rows; i++) {
        print_matrix->value[i] = (double *) calloc(1, print_matrix->mat_cols * sizeof(double));
        for (size_t j = 0; j < print_matrix->mat_cols; j++) {
            fscanf(ptr_filename, "%lf", &print_matrix->value[i][j]);
        }
    }
    fclose(ptr_filename);
    return print_matrix;
}
Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (!matrix) {
        puts("error: malloc return NULL");
        return NULL;
    }
    matrix->mat_rows = rows;
    matrix->mat_cols = cols;
    matrix->value = (double **) malloc(matrix->mat_rows * sizeof(double *));
    if (!matrix->value) {
        puts("error: malloc return NULL");
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < matrix->mat_cols; i++) {
        matrix->value[i] = (double *)malloc(matrix->mat_cols * sizeof(double));
        if (!matrix->value[i]) {
            puts("error: calloc return NULL");
            for (size_t k = 0; k < i; k++) {
                free(matrix->value[k]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->mat_cols; i++) {
        free(matrix->value[i]);
    }
    free(matrix->value);
    free(matrix);
}
// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix) {
        return 1;
    }
    *rows = matrix->mat_rows;
    return 0;
}
int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix) {
        return 1;
    }
    *cols = matrix->mat_cols;
    return 0;
}
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix) {
        return 1;
    }
    *val = matrix->value[row][col];
    return 0;
}
int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return 1;
    }
    matrix->value[row][col] = val;
    return 0;
}
// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }
    Matrix* mul_scalar_matrix = (Matrix *)malloc(sizeof(Matrix));
    if (!mul_scalar_matrix) {
        return NULL;
    }
    mul_scalar_matrix->value = (double **)malloc(matrix->mat_rows * (sizeof(double *)));
    if (!mul_scalar_matrix->value) {
        free(mul_scalar_matrix);
        return NULL;
    }
    for (size_t i = 0; i < matrix->mat_rows; i++) {
            mul_scalar_matrix->value[i] = (double *)malloc(matrix->mat_cols * sizeof(double));
            if (!mul_scalar_matrix->value[i]) {
                for (size_t k = 0; k < i; k++) {
                    free(mul_scalar_matrix->value[k]);
                }
                free(mul_scalar_matrix->value);
                free(mul_scalar_magtrix);
                return NULL;
            }
            (*mul_scalar_matrix->value[i]) = (*matrix->value[i]) * val;
    }
    return mul_scalar_matrix;
}
Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix* transp_matrix = (Matrix *)malloc(sizeof(Matrix));
    if (!transp_matrix) {
        return NULL;
    }
    transp_matrix->value = (double **)malloc(matrix->mat_rows * sizeof(double *));
    if (!transp_matrix->value) {
        free()
    }
}
/*Matrix* sum(const Matrix* l, const Matrix* r) {

}
Matrix* sub(const Matrix* l, const Matrix* r) {

}
Matrix* mul(const Matrix* l, const Matrix* r) {

}*/

