#include "stdio.h"

int main() {
    int sum = 0;
    int a, b;

    scanf("%d %d", &a, &b);
    if (a <= 0) {
        for (int i = 1; i <= 5; ++ i) {
            sum += i;
        }
    } else {
        if (b > 0) {
            for (int i = 2; i <= 10; i += 2) {
                sum += i;
            }
        }
    }
    if (sum > 15) {
        return -1;
    }
    return 0;
}