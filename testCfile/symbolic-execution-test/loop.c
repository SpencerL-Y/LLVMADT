#include "stdio.h"

int main() {
    int num = 0;
    for (int i = 0; i < 3; ++ i) {
        num = num + i;
    }
    if (num > 0) {
        return -1;
    }
    return 0;
}