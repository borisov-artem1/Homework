#include "utils.h"

void test_rw() {
    const char *filename = REC_DAT;

    struct some_data expected_data;
    // Fill `expected_data` with some test values
    // and write them into the file `f`.
    // ...
    write_to_file(filename, &expected_data);

    struct some_data got_data;
    read_from_file(filename, &got_data);

    // Compare any field from `expected_data` with any field from `got_data`
    // ....
}