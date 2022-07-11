#include "utils.h"

size_t timer_from(unsigned char from) {
    size_t counter = 0;
    for (char i = from; i >= 0; --i) {
        ++counter;
        printf("%c", i);
    }
    return counter;
}

// TODO(artemborisov): Implement `power of` function

int custom_pow(int base, int power) {
    for (int i = 0; i <= power; i++) {
        base *= base;
    }
    return base;
}

