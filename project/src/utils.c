#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        if (i == 0) {
            printf("%d\n", i);
        } else {
            printf("%d ", i);
        }
    }
    return counter;
}

// TODO(artemborisov): Implement `power of` function

int custom_pow(int base, int power) {
    int number = 1;
    for (int i = 0; i < power; i++) {
        number *= base;
    }
    return number;
}

