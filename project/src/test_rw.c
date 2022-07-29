#include "utils.h"
#include "test_case.h"
void test_rw_case(void) {
    const char *filename = REC_DATA;
    some_random_data expected_data;
    expected_data.test_num = 0;
    expected_data.test_cash_payments = 0;
    scanf("%d%20s%lf", &expected_data.test_num, expected_data.name, &expected_data.test_cash_payments);
    test_write_to_file(filename, &expected_data);
    some_random_data got_data;
    got_data.test_num = 0;
    got_data.test_cash_payments = 0;
    test_read_from_file(filename, &got_data);
    if (expected_data.test_num == got_data.test_num && expected_data.)
}
