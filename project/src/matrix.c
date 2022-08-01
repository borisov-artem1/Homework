#include "matrix.h"

// NOTE(stitaevskiy): Place your implementation here
// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE *Ptr_filename = NULL;
    Matrix *created_matrix;
    int check_fscanf = 0;
    Ptr_filename = fopen(path_file, "r");
    if (Ptr_filename == NULL) {
        puts("error: can't open file");
        return NULL;
    }
    check_fscanf = fscanf(path_file, "%d %d", creatred_matrix->rows, created->cols);
    if (check_fscanf != COUNT_ROWS_AND_COLS) {
        puts("error: can't scan rows and cols");
        return NULL;
    }
    if (created_matrix->rows < 0 || created_matrix->cols < 0) {
        puts("error: rows or cols are negative");
        return NULL;
    }
    for (size_t i = 0; i < (created_matrix->rows) * (created_matrix->cols); i++) {
        check_fscanf = fscanf(Ptr_filename, "%lf", created_matrix->value[i]);
        if (check_fscanf != 1) {
            puts("error: can't scan value");
            return NULL;
        }
    }
    printf("%d %d", created_matrix->rows, created_matrix->cols);
    for (size_t i = 0; i < (created_matrix->rows) * (created_matrix->cols); i++) {
        if ((i + 1) % created_matrix->rows == 0) {
            printf("%-12.5f\n", created_matrix->value[i]);
        } else {
            printf("%-12.5f", created_matrix->value[i]);
        }
    }
}
Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix;
    matrix->mat_rows = rows;
    matrix->mat_cols = cols;
    for (size_t i = 0; i < rows * cols; i++) {
        *((*matrix).value)[i] = (double *)calloc(1, sizeof(size_t));
        if (*((*matrix).value)[i] == NULL) {
            for (size_t k = 0; k < i; k++) {
                free(*((*matrix).value)[k]);
            }
            puts("error: not valid pointer");
            return NULL;
        }
    }
    return matrix;
}
void free_matrix(Matrix* matrix) {
    for (size_t i = 0; )
}