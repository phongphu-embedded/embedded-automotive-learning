#include <stdio.h>

void in_trang_thai(float *arr, char **ten, int n) {
    int i = 0;
    float nguong = 25.0f;

    for (i = 0; i < n; i++) {
        if (*(arr + i) < nguong) {
            printf("[%s] %.1f PSI - CANH BAO: Ap suat thap!\n",
                   ten[i], *(arr + i));
        }
        if (*(arr + i) >= nguong) {
            printf("[%s] %.1f PSI - OK\n",
                   ten[i], *(arr + i));
        }
    }
}

void tim_banh_thap_nhat(float *arr, char **ten, int n,
                        float *ap_suat_min, int *vi_tri) {
    int j = 0;
    *ap_suat_min = arr[0];
    *vi_tri = 0;

    for (j = 0; j < n; j++) {
        if (*(arr + j) < *ap_suat_min) {
            *ap_suat_min = *(arr + j);
            *vi_tri = j;
        }
    }
}

float tinh_ap_suat_trung_binh(float *arr, int n) {
    float tong = 0.0f;
    int k = 0;

    for (k = 0; k < n; k++) {
        tong = tong + *(arr + k);
    }
    return tong / (float)n;
}

int main(void) {
    float ap_suat[4] = {32.5f, 28.0f, 35.2f, 22.3f};
    char *ten_banh[4] = {"Truoc trai", "Truoc phai",
                         "Sau trai",   "Sau phai"};
    float ap_suat_min = 0.0f;
    int   vi_tri      = 0;
    float tb          = 0.0f;

    printf("=== HE THONG TPMS ===\n");
    in_trang_thai(ap_suat, ten_banh, 4);

    tb = tinh_ap_suat_trung_binh(ap_suat, 4);
    tim_banh_thap_nhat(ap_suat, ten_banh, 4, &ap_suat_min, &vi_tri);

    printf("\nAp suat trung binh : %.2f PSI\n", tb);
    printf("Banh thap nhat     : %s - %.1f PSI\n",
           ten_banh[vi_tri], ap_suat_min);

    return 0;
}