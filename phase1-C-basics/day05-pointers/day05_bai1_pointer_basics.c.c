#include <stdio.h>

int main(void) {
    int x = 10;
    int *p = &x;

    printf("Gia tri x    = %d\n",    x);
    printf("Dia chi x    = %p\n",     (void*)&x);
    printf("Dia chi p    = %p\n",     (void*)&p);
    printf("Gia tri p    = %p\n",     (void*)p);
    printf("Gia tri *p   = %d\n",     *p);

    *p = 99; /* Thay doi x thong qua con tro */
    printf("x sau *p=99  = %d\n",     x);

    return 0;
}