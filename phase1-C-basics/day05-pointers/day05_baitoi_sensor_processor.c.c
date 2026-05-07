#include <stdio.h>

float tinh_trung_binh(float *arr, int n)
                    /* Loai bien  ten mang, so phan tu lay*/
{
    float tong = 0;
    int i = 0;

    for (i = 0; i < n; i++) {
        tong = tong + *(arr + i);
    }
    return tong / n; 
}

int dem_vuot_nguong(float *arr, int n, float nguong) {
    int count = 0;
    int k = 0;

    for (k = 0; k < n; k++) {
        if (*(arr + k) > nguong) {
            count++;
        }
    }
    return count;
}

void tim_min_max(float *arr, int n, float *min, float *max) {
    *min = *(arr);
    *max = *(arr);
    int j = 0;

    for (j = 0; j < n; j++) {
        if (*(arr + j) > *max) {
            *max = *(arr + j);
        }
        if (*(arr + j) < *min) {
            *min = *(arr + j);
    }
    }
}

int main(void) {
    float nhiet_do[6] = {72.0f, 78.0f, 86.0f, 91.0f, 83.0f, 79.0f};
    float gia_tri_min, gia_tri_max;
    
    tim_min_max(nhiet_do, 6, &gia_tri_min, &gia_tri_max);
    float tb = tinh_trung_binh(nhiet_do, 6);
    int dem = dem_vuot_nguong(nhiet_do, 6, 85);

    printf("Gia tri min: %.1f | Gia tri max: %.1f\n", gia_tri_min, gia_tri_max);
    printf("Gia tri trung binh: %.2f\n", tb);
    printf("So lan vươt nguong: %d\n", dem);

    return 0;
}
