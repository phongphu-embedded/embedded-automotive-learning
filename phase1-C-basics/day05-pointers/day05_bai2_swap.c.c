#include <stdio.h>

/* Pass-by-value: KHONG hoat dong */
void swap_sai(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    /* a, b o day chi la BAN SAO - x, y ngoai main khong doi*/
}

/*Pass-by-pointer: DUNG */
void swap_dung(int *a, int*b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 5;
    int y = 10;

    printf("Truoc: x=%d, y=%d\n", x, y);
    swap_sai(x, y);
    printf("Sau swap_sai: x=%d, y=%d\n", x, y);

    swap_dung(&x, &y);
    printf("Sau swap_dung: x=%d, y=%d\n", x, y);

    return 0;
}