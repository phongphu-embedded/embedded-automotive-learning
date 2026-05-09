#include <stdio.h>
#include <string.h>

typedef void(*Handler_t)(float data);

typedef struct 
{
    int ma_lenh;  /* CAN message ID */
    char ten[20];
    Handler_t xu_ly;  /* function pointer toi ham xu ly */
} Lenh_t;


void xu_ly_nhiet_do(float data) {
    float nguong = 100.0f;
    if (data > nguong) {
        printf("Canh bao qua nhiet! %.1f\n", data);
    } else {printf("Nhiet do binh thuong: %.1f\n", data);}
}

void xu_ly_toc_do(float data) {
    float nguong = 5000.0f;
    if (data > nguong) {
        printf("Canh bao qua toc do! %.1f\n", data);
    } else {printf("Toc do cho phep: %.1f\n", data);}
    }


void xu_ly_dien_ap(float data) {
    float nguong = 200.0f;
    if (data > nguong) {
        printf("Canh bao dien ap cao! %.1f\n", data);
    } else {printf("Dien ap binh thuong: %.1f\n", data);}
}

void xu_ly_lenh(Lenh_t *bang, int n, int ma, float data) {
    int i = 0;

    for (i = 0; i < n; i++) {
        if(ma == bang[i].ma_lenh) {
            if (bang[i].xu_ly != NULL) {
            bang[i].xu_ly(data);
        }
        return;
    } 
} printf("Khong tim thay lenh ma: %d\n", ma);
}

int main(void) {

    Lenh_t cam_bien_nhiet;
    strcpy(cam_bien_nhiet.ten, "cb_nhiet");
    cam_bien_nhiet.ma_lenh = 100;
    cam_bien_nhiet.xu_ly = xu_ly_nhiet_do;

    if (cam_bien_nhiet.xu_ly != NULL) {
        cam_bien_nhiet.xu_ly(70.0f);
    }

    Lenh_t cam_bien_rpm;
    strcpy(cam_bien_rpm.ten, "cb_toc_do");
    cam_bien_rpm.ma_lenh = 150;
    cam_bien_rpm.xu_ly = xu_ly_toc_do;

    if(cam_bien_rpm.xu_ly != NULL) {
        cam_bien_rpm.xu_ly(1500.0f);
    }

    Lenh_t cam_bien_dien_ap;
    strcpy(cam_bien_dien_ap.ten, "cb_dien_ap");
    cam_bien_dien_ap.ma_lenh = 200;
    cam_bien_dien_ap.xu_ly = xu_ly_dien_ap;

    if (cam_bien_dien_ap.xu_ly != NULL) {
        cam_bien_dien_ap.xu_ly(220.0f);
    }

    Lenh_t bang_lenh[3] = {
        {100, "cb_nhiet", xu_ly_nhiet_do},
        {150, "cb_toc_do", xu_ly_toc_do},
        {200, "cb_dien_ap", xu_ly_dien_ap}
    };

    xu_ly_lenh(bang_lenh, 3, 100, 200.0); /*ma lenh 100, xu ly nhiet do voi data là 200*/
    xu_ly_lenh(bang_lenh, 3, 150, 400.0);
    xu_ly_lenh(bang_lenh, 3, 888, 600.0);
    return 0;
}