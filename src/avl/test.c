#include <stdio.h>

void mul(int *a);

int main() {

    int a = 2;

    printf("%d ", a);
    mul(&a);
    printf("%d\n", a);
}

void mul(int *a) {
    int b = 3;
    int *p = &b;
    a = a+b;
}
