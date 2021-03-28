#include "stdio.h"

int main() {
    int a;
    int *p;
    p = &a;
    a = 10;
    if (*p > 3) {
        return -1;
    }
}