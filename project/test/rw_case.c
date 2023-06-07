#include "test_case.h"

void write_to_file(const char *filename, some_data *expected_data) {
    FILE *file_rec_dat = NULL;
    file_rec_dat = fopen(filename, "w");
    if (file_rec_dat == NULL) {
        puts("error");
        return;
    }
    scanf("%20d%20s%20lf", &((*expected_data).test_number),
                (*expected_data).test_name,
                &((*expected_data).test_cash_payments));
    fprintf(file_rec_dat, "%20d%20s%20lf", (*expected_data).test_number,
                (*expected_data).test_name, (*expected_data).test_cash_payments);
    fclose(file_rec_dat);
}

void read_from_file(const char *filename, some_data *data) {
    FILE *file_rec_dat = NULL;
    file_rec_dat = fopen(filename, "r+");
    if (file_rec_dat == NULL) {
        puts("error");
        return;
    }
    fscanf(file_rec_dat, "%20d%20s%20lf", &((*data).test_number),
           (*data).test_name, &((*data).test_cash_payments));
    fclose(file_rec_dat);
}
