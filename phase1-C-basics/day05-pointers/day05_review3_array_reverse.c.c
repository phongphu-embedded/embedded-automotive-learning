#include <stdio.h>

void dao_nguoc_mang(float *arr, int n) {
    int i = 0;
    float temp = 0.0f;

    for ( i = 0; i < n/2; i++) {
        temp = *(arr + i);
        *(arr + i) = *(arr + n - 1 - i);
        *(arr + n - 1 - i) = temp;
        }
}

int main(void){
    int j = 0;
    float mang[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    dao_nguoc_mang(mang, 5);
    for ( j = 0; j < 5; j++) {
        printf("{%.1f}, ", mang[j]);
    }
    return 0;
}