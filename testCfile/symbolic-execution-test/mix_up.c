#include "stdio.h"
#include "assert.h"

int main() {
    int x = 3, y = 1;
    int a, b;
    scanf("%d %d", &a, &b);
    if (x + a < y) {
        int c = x / b;
        if (c == -4) {
            return -1;
        }
    }
    return 0;
}