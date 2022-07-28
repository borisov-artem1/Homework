#ifndef MY_PROJECTC2_TEST_CASE_H
#define MY_PROJECTC2_TEST_CASE_H
#include "utils.h"
void test_write_to_file(const char *filename, some_random_data expected_data);
void test_read_from_file(const char *filename, some_random_data got_data);
void test_rw_case(void);
#endif // MY_PROJECTC2_TEST_CASE_H
