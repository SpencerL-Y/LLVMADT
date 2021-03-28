#include "stdio.h"

int main() {
    int* arr = (int*)malloc(12);
    int *p = arr;
    * (p + 5) = 3;
}