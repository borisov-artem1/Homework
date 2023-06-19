#include "matrix.h"
#define INVALID_STATUS_CODE "*** BEATEN PTR ***"
#define STATUS_CODE_ERROR "*** ROWS, COLS MISMATCHES MATRIX->ROWS, MATRIX->COLS ***"
#define ROW_COL_ERR "THE MATRICES ARE NOT CONSISTENT"
enum {
    STATUS_OK = 0,
    STATUS_ERR
};
// NOTE(stitaevskiy): Place your implementation here

Matrix* create_matrix_from_file(const char* path_file) {
    FILE *opened_file = fopen(path_file, "r+");
    size_t rows = 0;
    size_t cols = 0;
    if (opened_file == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    fscanf(opened_file, "%zu %zu", &rows, &cols);
    Matrix *return_matrix = create_matrix(rows, cols);
    if (return_matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    for (int i = 0; i < rows * cols; i++) {
        if (fscanf(opened_file, "%lf", matrix->data_arr[i]) == -1) {
            puts(STATUS_CODE_ERROR);
        }
    }
    fclose(opened_file);
    return return_matrix;
}
Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        //free(matrix);
        return NULL;
    }
    matrix->data_arr = calloc(rows * cols, sizeof(double));
    if (matrix->data_arr == NULL) {
        puts(INVALID_STATUS_CODE);
        //free(matrix->data_arr);
        //free(matrix);
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}
void free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return;
    }
    free(matrix->data_arr);
    free(matrix);
}
int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL || rows == NULL) {
        puts(INVALID_STATUS_CODE);
        return 1;
    }
    *rows = matrix->rows;
    return 0;
}
int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL || cols == NULL) {
        puts(INVALID_STATUS_CODE);
        return 1;
    }
    *cols = matrix->cols;
    return 0;
}
int get_elem(const Matrix* matrix, int row, int col, double* val) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return 1;
    }
    *val = matrix->data_arr[row * matrix->cols + col];
    return 0;
}
int set_elem(Matrix* matrix, int row, int col, double val) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return 1;
    }
    matrix->data_arr[row * matrix->cols + col] = val;
    return 0;
}
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    for (int i = 0; i < matrix->rows * matrix->cols; i++) {
        matrix->data_arr[i] *= val;
    }
    return matrix;
}
Matrix* transp(const Matrix* matrix) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    double tmp = 0;
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (j > i) {
                tmp = matrix->data_arr[i * matrix->cols + j];
                matrix->data_arr[i * matrix->cols + j] = matrix->data_arr[j * matrix->rows + i];
                matrix->data_arr[j * matrix->rows + i] = tmp;
            }
        }
    }
    return matrix;
}
Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    if (l->rows != r->rows && l->cols != r->cols) {
        puts(ROW_COL_ERR);
        return NULL;
    }
    Matrix* matrix = create_matrix(l->rows, l->cols);
    for (int i = 0; i < matrix->rows * matrix->cols; i++) {
        matrix->data_arr[i] = l->data_arr[i] + r->data_arr[i];
    }
    return matrix;
}
Matrix* sub(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    if (l->rows != r->rows && l->cols != r->cols) {
        puts(ROW_COL_ERR);
        return NULL;
    }
    Matrix* matrix = create_matrix(l->rows, l->cols);
    for (int i = 0; i < matrix->rows * matrix->cols; i++) {
        matrix->data_arr[i] = l->data_arr[i] - r->data_arr[i];
    }
    return matrix;
}
Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    if (l->cols != r->rows) {
        puts(ROW_COL_ERR);
        return NULL;
    }
    double eleml = 0.;
    double elemr = 0.;
    double total = 0.;
    Matrix* matrix = create_matrix(l->rows, r->cols);
    for (int i = 0; i < l->rows; i++) {
        for (int j = 0; j < r->cols; j++) {
            total = 0.;
            for (int k = 0; k < l->cols; k++) {
                get_elem(l, i, k, &eleml);
                get_elem(r, k, j, &elemr);
                total += eleml * elemr;
            }
            set_elem(matrix, i, j, total);
        }
    }
    return matrix;
}
int det(const Matrix* matrix, double* val) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return 1;
    }
    if (matrix->rows != matrix->cols) {
        puts(STATUS_CODE_ERROR);
        return 1;
    }
    *val = return_det(matrix);
    return 0;
}
double return_det(const Matrix *matrix) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return 0.;
    }
    if (matrix->rows == 1) {
        return ret_elem(matrix, 0, 0);
    }
    else if (matrix->rows == 2) {
        double val = ret_elem(matrix, 0, 0) * ret_elem(matrix, 1, 1)
                - ret_elem(matrix, 0, 1) * ret_elem(matrix, 1, 0);
        return val;
    } else {
        double answer = 0.;
        double sign = 1.;
        for (int i = 0; i < matrix->cols; i++) {
            Matrix *minor = del_row_col(matrix, 0, i);
            double mult = ret_elem(matrix, 0, i);
            double buf = return_det(matrix);
            answer += sign * mult * buf;
            sign *= -1.;
            free_matrix(minor);
        }
        return answer;
    }
}
double ret_elem(Matrix *matrix, int row, int col) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return 0.;
    }
    double *val = matrix->data_arr + (row * matrix->cols + col);
    return *val;
}
Matrix *del_row_col(Matrix *matrix, int row_p, int col_p) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    int rows = matrix->rows - 1;
    int cols = matrix->cols - 1;
    Matrix *new_matrix = create_matrix(rows, cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (i != row_p && j != col_p) {
                *new_matrix->data_arr = ret_elem(matrix, i, j);
                new_matrix->data_arr++;
            }
        }
    }
    return new_matrix;
}

Matrix* adj(const Matrix* matrix) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    if (matrix->cols < 2 && matrix->rows < 2) {
        puts(STATUS_CODE_ERROR);
        return NULL;
    }
    double val = 0.;
    Matrix *minor = NULL;
    double determinant = 0.;
    double comp_of_matrix = 0.;
    double sign = 1.;
    Matrix *new_matrix = create_matrix(matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            val = ret_elem(matrix, i, j);
            minor = del_row_col(matrix, i, j);
            det(minor, determinant);
            comp_of_matrix = sign * determinant;
            set_elem(new_matrix, i, j, comp_of_matrix);
            sign *= -1.;
            free_matrix(minor);
        }
    }
    return new_matrix;
}
Matrix* inv(const Matrix* matrix) {
    if (matrix == NULL) {
        puts(INVALID_STATUS_CODE);
        return NULL;
    }
    Matrix *adj_matrix = adj(matrix)
    double determinant = 0.;
    det(matrix, determinant);
    determinant = 1 / determinant;
    Matrix *inv_matrix = mul_scalar(adj_matrix, determinant);
    free_matrix(adj_matrix);
    return inv_matrix;
}
