#include "common.h"
#include <stdio.h>

int is_number(const char* str)
{
    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        str++;
    }
    return 1;
}