#include <stdio.h>

int main(void) {
    int i = 0;
    float nhiet_do_tong = 0.0f;
    float nhiet_do[8] = {60.0f, 65.0f, 70.0f, 75.0f,
    80.0f, 85.0f, 90.0f, 95.0f};
    float min = nhiet_do[0];
    float max = nhiet_do[0];
    int count = 0;

    for (i = 0; i < 8; i++) {
        nhiet_do_tong = nhiet_do_tong + nhiet_do[i];
        if (nhiet_do[i] > max) {
            max = nhiet_do[i];
                }
        if (nhiet_do[i] < min) {
            min = nhiet_do[i];
                }
        if (nhiet_do[i] > 85.0f) {
            printf("CANH BAO: Chu ky %d: %.2f do C\n", i +1, nhiet_do[i]);
            count++;
        }
    }
    printf("Nhiet do trung binh: %.2f do C\n", nhiet_do_tong/8.0f);
    printf("Nhiet do min: %.2f do C va max: %.2f do C\n", min, max);
    printf("So lan vuot nguong: %d/8\n", count);
    return 0;
}