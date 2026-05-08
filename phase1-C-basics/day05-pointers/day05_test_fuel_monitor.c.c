#include <stdio.h>

void cap_nhat_muc(float *arr, int n, float *muc_hien_tai) {
    int i = 0;

    for (i = 0; i < n; i++) {
        *muc_hien_tai = *(arr + i);
     }
     printf("Muc nhien lieu hien tai: %.1f %%\n", *muc_hien_tai);
}

int kiem_tra_canh_bao(float *muc, float nguong_thap, float nguong_day) {
    if (*muc < nguong_thap) {
        return 1;
    }
    else if (*muc > nguong_day) {
        return 2;
    }
    else {return 0;}
    
}

float tinh_muc_trung_binh(float *arr, int n) {
    int j = 0;
    float tong = 0.0f;

    for (j = 0; j < n; j++) {
        tong = tong + *(arr + j);
    }
    return tong / (float)n;
}

int main(void) {
    float nhien_lieu[5] = {80.0f, 65.0f, 45.0f, 20.0f, 55.0f}; /* % */
    float nguong_thap = 25.0f;
    float nguong_day  = 90.0f;
    float muc_hien_tai = 0.0f;

    cap_nhat_muc(nhien_lieu, 5, &muc_hien_tai);
    int trang_thai = kiem_tra_canh_bao(&muc_hien_tai, nguong_thap, nguong_day);

    if (trang_thai == 1) {
        printf("CANH BAO: Can do them nhien lieu!\n");
    } else if (trang_thai == 2) {
         printf("CANH BAO: Binh qua day!\n");
    } else {
        printf("Binh thuong\n");
    }
    float tb = tinh_muc_trung_binh(nhien_lieu, 5);
    printf("Muc trung binh: %.1f %%\n", tb);

    return 0;
}