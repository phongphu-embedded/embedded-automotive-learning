#include <stdio.h>

int cong(int a, int b) {return a + b;}
int tru(int a, int b) {return a - b;}
int nhan(int a, int b) {return a * b;}

int main(void) {
    int (*phep_tinh)(int, int) = NULL;
    int ket_qua = 0;

    phep_tinh = cong;
    ket_qua= phep_tinh(10, 3);
    printf("Cong: %d\n", ket_qua);

    phep_tinh = tru;
    ket_qua = phep_tinh(10, 3);
    printf("Tru: %d\n", ket_qua);

    phep_tinh = nhan;
    ket_qua = phep_tinh(10, 3);
    printf("Nhan: %d\n", ket_qua);

    return 0;
}