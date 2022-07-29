#include "test_case.h"
#include "utils.h"
void test_write_to_file(const char *filename, const some_random_data *expected_data) {
    FILE *Ptr = NULL;
    Ptr = fopen(filename, "w");
    if (Ptr == NULL) {
        puts("error: can't open file");
        return;
    } else {
            fprintf(Ptr, "%-11d%-20s%lf",
                    (*expected_data).test_num,
                    (*expected_data).test_name,
                    (*expected_data).test_cash_payments);
            fclose(Ptr);
    }
}
void test_read_from_file(const char *filename, some_random_data *got_data) {
    FILE *Ptr = NULL;
    Ptr = fopen(filename, "r");
    if (Ptr == NULL) {
        puts("error: can't open file");
        return;
    } else {
        fscanf(Ptr, "%d%20s%lf", &((*got_data).test_num),
               (*got_data).test_name,
               &((*got_data).test_cash_payments));
        fclose(Ptr);
    }
}
