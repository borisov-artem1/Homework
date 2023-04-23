#include "utils.h"

void test_rw() {
    const char *filename = REC_DAT;

    some_data expected_data;
    expected_data.test_number = 0;
    expected_data.test_cash_payments = 0;
    // Fill `expected_data` with some test values
    // and write them into the file `f`.
    // ...
    printf("%s", "input data:\n1. test_number\n2. test_name\n3. test_cash_payments\n");
    write_to_file(filename, &expected_data);

    some_data got_data;
    got_data.test_number = 0;
    got_data.test_cash_payments = 0;
    read_from_file(filename, &got_data);

    // Compare any field from `expected_data` with any field from `got_data`
    // ....
    if (expected_data.test_number == got_data.test_number &&
    expected_data.test_cash_payments == got_data.test_cash_payments &&
    expected_data.test_name == got_data.test_name) {
        puts("SUCCES");
        return;
    }
    printf("%-5d\n%-5d\n%-10s\n%-10s\n%-6lf\n%-6lf\n",
           expected_data.test_number,
           got_data.test_number,
           expected_data.test_name,
           got_data.test_name,
           expected_data.test_cash_payments,
           got_data.test_cash_payments);
    puts("ERROR");
}
