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
    if (print_matrix->mat_rows == 0 || print_matrix->mat_cols == 0) {
        puts("error: rows or cols equal to zero");
        free(print_matrix);
        fclose(ptr_filename);
        return NULL;
    }
    print_matrix->value = (double *)malloc(print_matrix->mat_rows * print_matrix->mat_cols * sizeof(double));
    if (!print_matrix->value) {
        puts("error: malloc return NULL");
        free(print_matrix);
        fclose(ptr_filename);
        return NULL;
    }
    for (size_t i = 0; i < print_matrix->mat_rows * print_matrix->mat_cols; i++) {
        check_fscanf = fscanf(ptr_filename, "%lf", &print_matrix->value[i]);
        if (check_fscanf != COUNT_ROWS_AND_COLS - 1) {
            puts("error: can't scan value[i]");
            free(print_matrix->value);
            free(print_matrix);
            fclose(ptr_filename);
            return NULL;
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
    matrix->value = (double *) malloc(matrix->mat_rows * matrix-> mat_cols * sizeof(double));
    if (!matrix->value) {
        puts("error: malloc return NULL");
        free(matrix);
        return NULL;
    }
    return matrix;
}
void free_matrix(Matrix* matrix) {
    free(matrix->value);
    free(matrix);
}
// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix) {
        return 1;
    }
    if (!rows) {
        return 1;
    }
    *rows = matrix->mat_rows;
    return 0;
}
int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix) {
        return 1;
    }
    if (!cols) {
        return 1;
    }
    *cols = matrix->mat_cols;
    return 0;
}
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix) {
        return 1;
    }
    if (!val) {
        return 1;
    }
    *val = matrix->value[matrix->mat_cols * row + col];
    return 0;
}
int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return 1;
    }
    matrix->value[matrix->mat_cols * row + col] = val;
    return 0;
}
// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }
    Matrix* out_matrix = create_matrix(matrix->mat_rows, matrix->mat_cols);
    if (!out_matrix) {
        return NULL;
    }
    out_matrix->mat_rows = matrix->mat_rows;
    out_matrix->mat_cols = matrix->mat_cols;
    for (size_t i = 0; i < matrix->mat_rows * matrix->mat_cols; i++) {
        out_matrix->value[i] = matrix->value[i] * val;
    }
    return out_matrix;
}
Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix* transpose_matrix = create_matrix(matrix->mat_rows, matrix->mat_cols);
    if (!transpose_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->mat_rows; i++) {
        for (size_t j = 0; j < matrix->mat_cols; j++) {
            transpose_matrix->value[j * matrix->mat_rows + i] = matrix->value[i * matrix->mat_cols + j];
        }
    }
    return transpose_matrix;
}
Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (l->mat_rows != r->mat_rows || l->mat_cols != r->mat_cols) {
        return NULL;
    }
    Matrix* matrix = create_matrix(l->mat_rows, l->mat_cols);
    if (!matrix) {
        return NULL;
    }
    for (size_t i = 0; i < l->mat_rows * l->mat_cols; i++) {
        matrix->value[i] = l->value[i] + r->value[i];
    }
    return matrix;
}
Matrix* sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (l->mat_rows != r->mat_rows || l->mat_cols != r->mat_cols) {
        return NULL;
    }
    Matrix* matrix = create_matrix(l->mat_rows, l->mat_cols);
    if (!matrix) {
        return NULL;
    }
    for (size_t i = 0; i < l->mat_rows * l->mat_cols; i++) {
        matrix->value[i] = l->value[i] - r->value[i];
    }
    return matrix;
}
Matrix* mul(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    Matrix* mul_matrix = create_matrix(r->mat_rows, r->mat_cols);
    if (!mul_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < l->mat_rows; i++) {
        for (size_t j = 0; j < r->mat_cols; j++) {
            mul_matrix->value[i * l->mat_cols + j] = 0;
            for (size_t k = 0; k < l->mat_cols; k++) {
                mul_matrix->value[i * l->mat_cols + j] +=
                        l->value[i * l->mat_cols + k] *
                        r->value[k * r->mat_rows + j];
            }
        }
    }
    return mul_matrix;
}
// Extra operations
int det(const Matrix* matrix, double* val) {
    if (!matrix) {
        return 1;
    }
    if (!val) {
        return 1;
    }
    if (matrix->mat_rows == 0 || matrix->mat_cols == 0) {
        return 1;
    }
    double sum_val = 0;
    double mul_val = 0;
    for (size_t j = 0; j < matrix->mat_rows * matrix->mat_cols; j += matrix->mat_rows) {
        sum_val += mul_val;
        mul_val = 1;
        for (size_t i = 0; i < matrix->mat_rows; i++) {
            mul_val *= matrix->value[(i * matrix->mat_cols + i + j) % (matrix->mat_rows * matrix->mat_cols)];
        }
    }
    for (size_t j = matrix->mat_rows; j > 0; j--) {
        sum_val -= mul_val;
        mul_val = 1;
        for (size_t i = 0; i < matrix->mat_rows; i++) {
            mul_val *= matrix->value[(i * (matrix->mat_cols - 2) + i + j - 1)
                                     % (matrix->mat_rows * matrix->mat_rows)];
        }
    }
    *val = sum_val;
    return 0;
}
Matrix* adj(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix* transpose_matrix = create_matrix(matrix->mat_rows, matrix->mat_cols);
    if (!transpose_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->mat_rows; i++) {
        for (size_t j = 0; j < matrix->mat_cols; j++) {
            transpose_matrix->value[j * matrix->mat_rows + i] = matrix->value[i * matrix->mat_cols + j];
        }
    }
    return transpose_matrix;
}
Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix* transpose_matrix = create_matrix(matrix->mat_rows, matrix->mat_cols);
    if (!transpose_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->mat_rows; i++) {
        for (size_t j = 0; j < matrix->mat_cols; j++) {
            transpose_matrix->value[j * matrix->mat_rows + i] = matrix->value[i * matrix->mat_cols + j];
        }
    }
    return transpose_matrix;
}
