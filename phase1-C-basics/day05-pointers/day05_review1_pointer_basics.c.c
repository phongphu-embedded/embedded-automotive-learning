#include <stdio.h>

int main(void) {
    /* Cho sẵn — KHÔNG ĐƯỢC THÊM BIẾN MỚI */
    int a = 100;
    int b = 200;
    int *p = &a;

    printf("%d\n", *p); /* Lay gia tri cua con tro p*/
    *p = 999;
    printf("%d\n", *p);
    p = &b;
    printf("%d\n", *p);
    return 0;
}

