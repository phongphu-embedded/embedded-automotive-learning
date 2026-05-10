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

void xu_ly_engine (void *self) {
     float nguong = 100.0f;
     ECU_t *e = (ECU_t *)self; 
    
     printf("[%s] Nhiet do: %.1fC", e->ten, e->nhiet_do);
    
     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!\n");
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
    
     printf("[%s] Nhiet do: %.1fC", e->ten, e->nhiet_do);
    
     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!\n");
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
    
     printf("[%s] Nhiet do: %.1fC", e->ten, e->nhiet_do);
    
     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!\n");
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
    
     printf("[%s] Nhiet do: %.1fC", e->ten, e->nhiet_do);
    
     if (e->nhiet_do > nguong) {
        printf(" | CANH BAO: Qua nhiet!!\n");
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

    for (i = 0; i < n; i++) {
        if (arr[i].xu_ly != NULL) {
            arr[i].xu_ly(&arr[i]);
        }
    }
}

void thong_ke(ECU_t *arr, int n,
              int *so_ecu_on, int *so_ecu_loi,
              float *nhiet_do_tb) {
    int j = 0;
    float tong = 0.0f;

    *so_ecu_loi = 0;
    *so_ecu_on = 0;

    for (j = 0; j < n; j++) {
        if (arr[j].trang_thai == 1) {
            (*so_ecu_on)++;
        } else if (arr[j].trang_thai == 2) {
            (*so_ecu_loi)++;
        }
        tong = tong + arr[j].nhiet_do;
    }
    *nhiet_do_tb = tong / (float)n;
}


void khoi_tao_ecu(ECU_t *e, int id, char *ten,
                  float nhiet_do, int trang_thai,
                  void (*xu_ly)(void *self))
    {
     e->id =  id;
     strcpy(e->ten, ten);
     e->nhiet_do = nhiet_do;
     e->trang_thai = trang_thai;
     e->xu_ly = xu_ly;
    }

void in_ecu_loi(ECU_t *arr, int n) {
 /* Yêu cầu: In ra tên và nhiệt độ của các ECU có trang_thai == 2.*/
    
    int k = 0;
    for (k = 0; k < n; k++) {
        if (arr[k].trang_thai == 2) {
            printf("%s dang co loi: nhiet do %.1fC\n", arr[k].ten, arr[k].nhiet_do);
        }
    }

int dem_ecu_qua_nhiet(ECU_t *arr, int n, float nguong) 
/*Yêu cầu: Đếm và trả về số ECU có nhiet_do > nguong.*/{
    int a = 0;
    int count = 0;

    for (a = 0; a < n; a++) {
        if (arr[a].nhiet_do > nguong) {
            count++;
        }
    } return count;
}

}
int main(void) {
    

    ECU_t ecu[4];
    int on = 0, loi = 0;
    float tb = 0.0f;
    float nhiet_do_log[LOG_SIZE] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    int log_index = 0;
    int i = 0;

    khoi_tao_ecu(&ecu[0], 1, "ECU_Engine", 92.0f, 1, xu_ly_engine);
    khoi_tao_ecu(&ecu[1], 2, "ECU_ABS", 75.0f, 1, xu_ly_abs);
    khoi_tao_ecu(&ecu[2], 3, "ECU_Airbag", 110.0f, 2, xu_ly_airbag);
    khoi_tao_ecu(&ecu[3], 4, "ECU_BCM", 68.0f, 0, xu_ly_bcm);

    printf("=== QUET LAN 1 ===\n");
    quet_he_thong(ecu, 4);
    thong_ke(ecu, 4, &on, &loi, &tb);
    printf("ECU ON: %d | Loi: %d | TB: %.2fC\n\n", on, loi, tb);

    /* Ghi vao circular buffer */
    nhiet_do_log[log_index] = tb;
    log_index = (log_index + 1) % LOG_SIZE;
    
    /* Lan quet 2 — doi nhiet do */
    ecu[0].nhiet_do = 105.0f;  /* engine nong hon */
    ecu[3].nhiet_do = 72.0f;   /* BCM tang len */

    printf("=== QUET LAN 2 ===\n");
    quet_he_thong(ecu, 4);
    thong_ke(ecu, 4, &on, &loi, &tb);
    printf("ECU ON: %d | Loi: %d | TB: %.2fC\n\n", on, loi, tb);
    nhiet_do_log[log_index] = tb;
    log_index = (log_index + 1) % LOG_SIZE;

    /* Lan quet 3 — doi nhiet do */
    ecu[1].nhiet_do = 88.0f;   /* ABS tang */
    ecu[2].nhiet_do = 95.0f;   /* Airbag giam */

    printf("=== QUET LAN 3 ===\n");
    quet_he_thong(ecu, 4);
    thong_ke(ecu, 4, &on, &loi, &tb);
    printf("ECU ON: %d | Loi: %d | TB: %.2fC\n\n", on, loi, tb);
    nhiet_do_log[log_index] = tb;
    log_index = (log_index + 1) % LOG_SIZE;

    /* In log */
    printf("=== LOG NHIET DO TB ===\n");
    for (i = 0; i < LOG_SIZE; i++) {
        if (nhiet_do_log[i] > 0.0f) {
            printf("[%d]: %.2fC\n", i, nhiet_do_log[i]);
        } else {
            printf("[%d]: ---\n", i);
        }
    }

    return 0;
}