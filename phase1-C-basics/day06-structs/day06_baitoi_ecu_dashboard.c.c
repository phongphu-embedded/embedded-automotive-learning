#include <stdio.h>
#include <string.h>

typedef struct 
{
    char ten[20];  /*ten cam bien*/
    float gia_tri;  /*gia tri do duoc*/
    float nguong_max; /* nguong canh bao*/
    int don_vi;    /* 0=C, 1=V, 2=RPM, 3=atm*/
} Cambien_t;

void kiem_tra_canh_bao(Cambien_t *s, int n) {
    int i = 0;

    for (i = 0; i < n; i++) {
        if (s[i].gia_tri > s[i].nguong_max) {
           printf("Canh bao qua nguong: %s\n", s[i].ten);
        } else {
            printf("Binh thuong: %s\n", s[i].ten);
        }
    }
}

void in_dashboard(Cambien_t *arr, int n) {
    int j = 0;
    char * in_don_vi[4] = {"C", "V", "RPM", "atm"};

    printf("ECU DASHBOARD\n");

    for (j = 0; j < 4; j++) {
        if (arr[j].gia_tri > arr[j].nguong_max) {
        printf("%d | %s | %.2f %s | Canh bao qua nguong\n",
             j + 1, arr[j].ten, arr[j].gia_tri, in_don_vi[arr[j].don_vi]);    
        } else {
            printf("%d | %s | %.2f %s | Binh thuong\n",
             j + 1, arr[j].ten, arr[j].gia_tri, in_don_vi[arr[j].don_vi]);
                }
    }
}

int main(void) {
    Cambien_t sensor[4];

    strcpy(sensor[0].ten, "tocdo");
    sensor[0].gia_tri = 90.0f;
    sensor[0].nguong_max = 60.0f;
    sensor[0].don_vi = 2;

    strcpy(sensor[1].ten, "dienap");
    sensor[1].gia_tri = 220.0f;
    sensor[1].nguong_max = 500.0f;
    sensor[1].don_vi = 1;
    
    strcpy(sensor[2].ten, "nhietdo");
    sensor[2].gia_tri = 70.0f;
    sensor[2].nguong_max = 100.0f;
    sensor[2].don_vi = 0;

    strcpy(sensor[3].ten, "apsuat");
    sensor[3].gia_tri = 40.0f;
    sensor[3].nguong_max = 150.0f;
    sensor[3].don_vi = 3;

    kiem_tra_canh_bao(sensor, 4);
    in_dashboard(sensor, 4);

    return 0;
}

