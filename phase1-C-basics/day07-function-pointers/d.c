#include <stdio.h>
#include <string.h>
#define LOG_SIZE 5
typedef struct {
    int         id;            /* ECU ID */
    char        ten[20];       /* tên ECU */
    float       nhiet_do;      /* nhiệt độ hoạt động */
    int         trang_thai;    /* 0=off, 1=on, 2=loi */
    void (*xu_ly)(void *self); /* function pointer tự xử lý */
} ECU_t;

void khoi_tao_ecu(ECU_t *e, int id, char *ten,
                  float nhiet_do, int trang_thai,
                  void (*xu_ly)(void *self)) {
    e->id = id;
    strcpy(e->ten, ten);
    e->nhiet_do = nhiet_do;
    e->trang_thai = trang_thai;
    e->xu_ly = xu_ly;
                  }

void xu_ly_engine (void *self) {
     float nguong = 100.0f;
     ECU_t *e = (ECU_t *)self;

     printf("[%s] Nhiet do: %.1f", e->ten, e->nhiet_do);

     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!");
     }

     if (e->trang_thai == 2) {
        printf(" | CANH BAO: Loi ECU!\n");
     } else if (e->trang_thai == 1) {
        printf(" | Trang thai: ON\n");
     } else {
        printf(" | Trang thai: OFF\n");
     }
}

void xu_ly_abs    (void *self) {
     float nguong = 100.0f;
     ECU_t *e = (ECU_t *)self;

     printf("[%s] Nhiet do: %.1f", e->ten, e->nhiet_do);

     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!");
     }

     if (e->trang_thai == 2) {
        printf(" | CANH BAO: Loi ECU!\n");
     } else if (e->trang_thai == 1) {
        printf(" | Trang thai: ON\n");
     } else {
        printf(" | Trang thai: OFF\n");
     }
}

void xu_ly_airbag (void *self) {
     float nguong = 100.0f;
     ECU_t *e = (ECU_t *)self;

     printf("[%s] Nhiet do: %.1f", e->ten, e->nhiet_do);

     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!");
     }

     if (e->trang_thai == 2) {
        printf(" | CANH BAO: Loi ECU!\n");
     } else if (e->trang_thai == 1) {
        printf(" | Trang thai: ON\n");
     } else {
        printf(" | Trang thai: OFF\n");
     }
}

void xu_ly_bcm    (void *self) {
     float nguong = 100.0f;
     ECU_t *e = (ECU_t *)self;

     printf("[%s] Nhiet do: %.1f", e->ten, e->nhiet_do);

     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!");
     }

     if (e->trang_thai == 2) {
        printf(" | CANH BAO: Loi ECU!\n");
     } else if (e->trang_thai == 1) {
        printf(" | Trang thai: ON\n");
     } else {
        printf(" | Trang thai: OFF\n");
     }
}

void quet_he_thong(ECU_t *arr, int n) {
     int i = 0;

     for(i = 0; i < n; i++) {
        if (arr[i].xu_ly != NULL) {
            arr[i].xu_ly(&arr[i]); 
        }
     }
}

void thong_ke(ECU_t *arr, int n,
              int *so_ecu_on, int *so_ecu_loi,
              float *nhiet_do_tb) {

    int i = 0;
    float tong = 0.0f;

    *so_ecu_loi = 0;
    *so_ecu_on = 0;
    *nhiet_do_tb = 0;

    for (i = 0; i < n; i++) {
         if (arr[i].trang_thai ==1) {
            (*so_ecu_on)++;
         } else if (arr[i].trang_thai == 2) {
            (*so_ecu_loi)++;
         }
    tong = tong + arr[i].nhiet_do;
    } 
    *nhiet_do_tb = tong / (float)n;
              }

int main(void) {
    /* Sau mỗi lần gọi thong_ke */
    float  nhiet_do_log[LOG_SIZE] = {
        0.0f , 0.0f, 0.0f, 0.0f, 0.0f};
    int log_index = 0;
    int ecu_on = 0;
    int ecu_loi = 0;
    float tb = 0.0f;

    nhiet_do_log[log_index] = tb;
    log_index = (log_index + 1) % LOG_SIZE;


    ECU_t ecu[4];

    khoi_tao_ecu(&ecu[0], 1, "ECU_Engine", 92.0f, 1, xu_ly_engine);
    khoi_tao_ecu(&ecu[1], 2, "ECU_ABS", 75.0f, 1, xu_ly_abs);
    khoi_tao_ecu(&ecu[2], 3, "ECU_Airbag", 110.0f, 2, xu_ly_airbag);
    khoi_tao_ecu(&ecu[3], 4, "ECU_BCM", 68.0f, 0, xu_ly_bcm);
    
    printf("Quet lan 1");
    quet_he_thong(ecu, 4);
    thong_ke(ecu, 4, &ecu_on, &ecu_loi, &tb);
    printf(" ECU ON: %d | Loi: %d | TB: %.2f \n", ecu_on, ecu_loi, tb);

    nhiet_do_log[log_index] = tb;
    log_index = (log_index + 1) % LOG_SIZE;
   

    


    return 0;
}