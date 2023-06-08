#include "test_case.h"
#include <string.h>
#define SUCCESS_STATUS_CODE "--SUCCESS--"
#define INVALID_STATUS_CODE "--ERROR--"
#define TEST_FILENAME "test_file.dat"

void test_rw(void) {

    const char *filename = TEST_FILENAME;
    some_data expected_data = {0};
    // Fill `expected_data` with some test values
    // and write them into the file `f`.
    // ...
    char expected_string[100];
    printf("%s", "input data:\n1. test_number\n2. test_name\n3. test_cash_payments\n");
    write_to_file(filename, &expected_data);
    snprintf(expected_string, 100, "%20d%20s%20lf", expected_data.test_number, expected_data.test_name, expected_data.test_cash_payments);
    some_data got_data = {0};
    read_from_file(filename, &got_data);
    char got_string[100];
    snprintf(got_string, 100, "%20d%20s%20lf", got_data.test_number, got_data.test_name, got_data.test_cash_payments);
    if (strcmp(expected_string, got_string) == 0) {
        printf("Expected data:\n%-5d%-10s%-6lf\n\n",
               expected_data.test_number,
               expected_data.test_name,
               expected_data.test_cash_payments);
        printf("Got data:\n%-5d%-10s%-6lf\n\n",
               got_data.test_number,
               got_data.test_name,
               got_data.test_cash_payments);
        puts(SUCCESS_STATUS_CODE);
        return;
    } else {
        puts(INVALID_STATUS_CODE);
    }
}
int main (void) {
    test_rw();
    return 0;
}