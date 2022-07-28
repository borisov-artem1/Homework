#include "test_case.h"
#include "utils.h"
void test_write_to_file(const char *filename, some_random_data expected_data) {
    FILE *Ptr = NULL;
    Ptr = fopen(filename, "w");
    if (Ptr == NULL) {
        puts("error: can't open file")
        return;
    } else {

    }
}
void test_read_from_file(const char *filename, some_random_data got_data) {

}
