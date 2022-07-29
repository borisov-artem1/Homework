#ifndef PROJECT_INCLUDE_TEST_CASE_H_
#define PROJECT_INCLUDE_TEST_CASE_H_
#include "utils.h"
void test_write_to_file(const char *filename, const some_random_data *expected_data);
void test_read_from_file(const char *filename, some_random_data *got_data);
void test_rw_case(void);
#endif  // PROJECT_INCLUDE_TEST_CASE_H_
