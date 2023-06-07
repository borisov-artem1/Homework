#ifndef PROJECT_INCLUDE_TEST_CASE_H_
#define PROJECT_INCLUDE_TEST_CASE_H_
typedef struct Some_data {
    int test_number;
    char test_name[20];
    double test_cash_payments;
} some_data;

void test_rw(void);
void write_to_file(const char *filename, some_data *expected_data);
void read_from_file(const char *filename, some_data *data);

#endif  // PROJECT_INCLUDE_TEST_CASE_H_
