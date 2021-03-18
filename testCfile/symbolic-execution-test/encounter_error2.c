#include "stdio.h"

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    int z = 2 * y;
    if (z == x) {
        if (x > y + 10) {
            return -1;
        }
    }
    return 0;
}