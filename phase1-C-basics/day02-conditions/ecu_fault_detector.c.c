#include <stdio.h>

int main(void) {
    float nhietdo = 80.0f;
    float dienap = 13.2f;
    int denpha = 0; /*0 la hong*/
    int coloi = 0;

    if (nhietdo > 90.0f) {
        printf("Loi: qua nhiet\n");
        coloi = 1;
    }
    if (dienap < 11.5f) {
        printf("Loi: Acquy\n");
        coloi = 1;
    }
    if (denpha == 0) {
        printf("Canhbao: den hong\n");
        coloi = 1;
    }
    if (coloi == 0) {
        printf("He thong binh thuong\n");
    }
    return 0;
}