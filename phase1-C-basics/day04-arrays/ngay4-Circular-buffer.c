#include <stdio.h>
#define BUFFER_SIZE 5

int main(void) {
    float buffer[BUFFER_SIZE] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    int vi_tri_ghi = 0;
    float data_in[8] = {65.0f, 70.0f, 75.0f, 80.0f, 85.0f, 90.0f, 72.0f, 68.0f};
    int i = 0;
    int j = 0;

    for (i = 0; i < 8; i++) {
        buffer[vi_tri_ghi] = data_in[i];
        vi_tri_ghi = (vi_tri_ghi + 1) % BUFFER_SIZE;

        printf("Ghi lan: %d, buffer hien tai\n", i + 1);
       
        
        for (j = 0; j < BUFFER_SIZE; j++) {
            printf("%.1f ", buffer[j]);
            
            if (buffer[j] > 75.0f) {
            printf(" (Qua nhiet) ");
        }
            }
        printf("\n");

        
    }
    return 0;
}
