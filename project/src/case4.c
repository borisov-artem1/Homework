#include "case4.h"
void print_int_number(int num) {
    if (num == 1) {
        printf("%d", 1);
        return;
    }
    if (num > 0) {
        print_int_number(num - 1);
        printf(" %d", num);
    }
    if (num < 1) {
        print_int_number(num + 1);
        printf(" %d", num);
    }
}
