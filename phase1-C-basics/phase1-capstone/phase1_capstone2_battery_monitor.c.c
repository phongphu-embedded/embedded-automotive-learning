#include <stdio.h>
#include <string.h>
#define theo_doi_size 5

typedef struct {
    int   id;
    char  ten[20];
    float dien_ap;      /* Volt */
    float nhiet_do;     /* do C */
    int   trang_thai;   /* 0=off, 1=on, 2=loi */
    void (*kiem_tra)(void *self);
} Pin_t;

void khoi_tao_pin(Pin_t *p, int id, char *ten,
                  float dien_ap, float nhiet_do,
                  int trang_thai, void (*kiem_tra)(void *self)){
    p->id = id;
    strcpy(p->ten, ten);
    p->dien_ap = dien_ap;
    p->nhiet_do = nhiet_do;
    p->trang_thai = trang_thai;
    p->kiem_tra = kiem_tra;
}

void kiem_tra_pin_a(void *self){
    Pin_t *e = (Pin_t *)self;

    printf("%s: dien ap %.1fV | nhiet do: %.1fC\n",
    e->ten, e->dien_ap, e->nhiet_do);

    if(e->dien_ap < 3.0f) {
        printf("CANH BAO: Dien ap thap!\n");
    } else {printf("Dien ap binh thuong\n");}
    
    if(e->nhiet_do > 80.0f) {
        printf("CANH BAO: Qua nhiet!\n");
    } else {printf("Nhiet do binh thuong\n");}

    if(e->trang_thai == 2) {
        printf("CANH BAO: Loi pin!\n");
    } else if (e->trang_thai == 1) {
           printf("Pin ON\n");
    } else {
        printf("Pin OFF\n");
    }
}
void kiem_tra_pin_b(void *self) {
    Pin_t *e = (Pin_t *)self;

    printf("%s: dien ap %.1fV | nhiet do: %.1fC\n",
    e->ten, e->dien_ap, e->nhiet_do);

    if(e->dien_ap < 3.0f) {
        printf("CANH BAO: Dien ap thap!\n");
    } else {printf("Dien ap binh thuong\n");}
    
    if(e->nhiet_do > 80.0f) {
        printf("CANH BAO: Qua nhiet!\n");
    } else {printf("Nhiet do binh thuong\n");}

    if(e->trang_thai == 2) {
        printf("CANH BAO: Loi pin!\n");
    } else if (e->trang_thai == 1) {
           printf("Pin ON\n");
    } else {
        printf("Pin OFF\n");
    }
}

void kiem_tra_pin_c(void *self) {
    Pin_t *e = (Pin_t *)self;

    printf("%s: dien ap %.1fV | nhiet do: %.1fC\n",
    e->ten, e->dien_ap, e->nhiet_do);

    if(e->dien_ap < 3.0f) {
        printf("CANH BAO: Dien ap thap!\n");
    } else {printf("Dien ap binh thuong\n");}
    
    if(e->nhiet_do > 80.0f) {
        printf("CANH BAO: Qua nhiet!\n");
    } else {printf("Nhiet do binh thuong\n");}

    if(e->trang_thai == 2) {
        printf("CANH BAO: Loi pin!\n");
    } else if (e->trang_thai == 1) {
           printf("Pin ON\n");
    } else {
        printf("Pin OFF\n");
    }
}

void kiem_tra_pin_d(void *self) {
    Pin_t *e = (Pin_t *)self;

    printf("%s: dien ap %.1fV | nhiet do: %.1fC\n",
    e->ten, e->dien_ap, e->nhiet_do);

    if(e->dien_ap < 3.0f) {
        printf("CANH BAO: Dien ap thap!\n");
    } else {printf("Dien ap binh thuong\n");}
    
    if(e->nhiet_do > 80.0f) {
        printf("CANH BAO: Qua nhiet!\n");
    } else {printf("Nhiet do binh thuong\n");}

    if(e->trang_thai == 2) {
        printf("CANH BAO: Loi pin!\n");
    } else if (e->trang_thai == 1) {
           printf("Pin ON\n");
    } else {
        printf("Pin OFF\n");
    }
}

void in_ket_qua(Pin_t *e, int n) {
    int z = 0;
    
    for (z = 0; z < n; z++) {
        if (e[z].kiem_tra != NULL) {
            e[z].kiem_tra(&e[z]);
        }
    }
}

void thong_ke(Pin_t *arr, int n, int *so_pin_on, 
              int *so_pin_loi, float *dien_ap_tb, 
              float*nhiet_do_tb) {
    int l = 0;
    float dien_tong = 0.0f;
    float nhiet_tong = 0.0f;
    *so_pin_on = 0;
    *so_pin_loi = 0;
    *nhiet_do_tb = 0.0f;
    *dien_ap_tb = 0.0f;


    for (l = 0; l < n; l++) {
        if (arr[l].trang_thai == 1) {
            (*so_pin_on)++;
        } else if (arr[l].trang_thai == 2) {
            (*so_pin_loi)++;
        }
        dien_tong = dien_tong + arr[l].dien_ap;
        nhiet_tong = nhiet_tong + arr[l].nhiet_do;
    }
    *nhiet_do_tb = nhiet_tong / (float)n;
    *dien_ap_tb = dien_tong / (float)n;
    
}
/*Trả về con trỏ tới pin có nhiệt độ cao nhất. */
Pin_t *tim_pin_nong_nhat(Pin_t *arr, int n) {
        
    int k = 0;
    Pin_t * max = &arr[0];
    
    for (k = 0; k < n; k++) {
        if (arr[k].nhiet_do > max->nhiet_do) {
            max = &arr[k];
        }
    } 
    return max;
}

int main(void) {
    int i = 0; 
    int pin_on = 0;
    int pin_loi = 0;
    float datb = 0.0f;
    float ndtb = 0.0f;

    float theo_doi_nhiet[theo_doi_size] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float theo_doi_dien[theo_doi_size] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    int lan_theo_doi = 0;

    Pin_t add_pin[4];

    khoi_tao_pin(&add_pin[0], 1, "Pin_A", 3.7f, 35.0f, 1, kiem_tra_pin_a);
    khoi_tao_pin(&add_pin[1], 2, "Pin_B", 2.8f, 82.0f, 1, kiem_tra_pin_b);
    khoi_tao_pin(&add_pin[2], 3, "Pin_C", 3.9f, 45.0f, 1, kiem_tra_pin_c);
    khoi_tao_pin(&add_pin[3], 4, "Pin_D", 3.5f, 91.0f, 1, kiem_tra_pin_d);
    

    /*Lan 1 khi viet ham*/
    in_ket_qua(add_pin, 4);
    thong_ke(add_pin, 4, &pin_on, &pin_loi, &datb, &ndtb);
    
    /*In lan 1*/
    printf("So pin ON: %d\n", pin_on);
    printf("So pin loi: %d\n", pin_loi);
    printf("Dien ap trung binh: %.1f V\n", datb);
    printf("NHiet do trung binh: %.1f C\n", ndtb);

    Pin_t *pin_nong = tim_pin_nong_nhat(add_pin, 4);
    printf("Pin nong nhat: pin %s - Nhiet do: %.1f\n", pin_nong->ten, pin_nong->nhiet_do);
    
    /*Cap nhat gia tri lan 1*/
    theo_doi_nhiet[lan_theo_doi] = ndtb;
    theo_doi_dien[lan_theo_doi] = datb;
    lan_theo_doi = (lan_theo_doi +1) % theo_doi_size;

    /*Lan 2*/
    /*Nap du lieu*/
    add_pin[1].nhiet_do = 95.0f; 
    add_pin[3].dien_ap  = 2.5f;

    /*Quet lan2*/
    printf("\n=== QUET LAN 2 ===\n");
    in_ket_qua(add_pin, 4);
    thong_ke(add_pin, 4, &pin_on, &pin_loi, &datb, &ndtb);

    /*In lan 2*/
    printf("So pin ON: %d\n", pin_on);
    printf("So pin loi: %d\n", pin_loi);
    printf("Dien ap trung binh: %.1f V\n", datb);
    printf("NHiet do trung binh: %.1f C\n", ndtb);
    
    
    /*Cap nhat gia tri lan 1*/
    theo_doi_nhiet[lan_theo_doi] = ndtb;
    theo_doi_dien[lan_theo_doi] = datb;
    lan_theo_doi = (lan_theo_doi +1) % theo_doi_size;

    /*In theo doi nhiet*/
    printf("\n=== LOG NHIET DO TB ===\n");
    for ( i = 0; i < theo_doi_size; i++) {
        if (theo_doi_nhiet[i] > 0.0f) {
            printf("[%d]: %.2fC\n", i, theo_doi_nhiet[i]);
            } else {
                printf("[%d]: ---\n", i);
            }
    }
    Pin_t *pin_nong_1 = tim_pin_nong_nhat(add_pin, 4);
    printf("Pin nong nhat: pin %s - Nhiet do: %.1f\n", pin_nong_1->ten, pin_nong_1->nhiet_do);


    return 0;
}