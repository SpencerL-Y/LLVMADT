#include "stdio.h"

int main() {
    int *p;
    int *q = p;
    int **pp;
    pp = &q;
    **pp = 3;
}