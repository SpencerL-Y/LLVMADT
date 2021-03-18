#include "stdio.h"
#include "assert.h"

int main() {
    int x = 1, y = 0;
    int a, b;
    scanf("%d %d", &a, &b);
    if (a != 0) {
        y = 3 + x;
        if (b == 0) {
            x = 2 * (a + b);
        }
        if (x - y == 0) {
            return -1;
        }
    }
    return 0;
}