#include "stdio.h"

int main() {
    int sum = 0;
    int b;
    scanf("%d", &b);
    if (b > 0) {
        sum ++;
    }
    for (int i = 1; i <= 5; ++ i) {
        sum += i;
    }
    if (sum > 15) {
        return -1;
    }
    return 0;
}