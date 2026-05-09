#include <stdio.h>
#include <string.h>

typedef struct 
{
    char ten[20];
    float nguong;
    int (*kiem_tra)(float gia_tri, float nguong, char * ten);
} CanhBao_t;

int kiem_tra_qua_nong(float gia_tri, float nguong, char * ten) {
    if (gia_tri > nguong) {
        printf("Canh bao qua nong tai %s\n", ten);
        return 1;
    } 
    else { 
        printf("%s binh thuong\n", ten);
        return 0;
    }
}

int kiem_tra_qua_thap(float gia_tri, float nguong, char *ten) {
    if (gia_tri < nguong) {
         printf("Canh bao qua thap tai %s\n", ten);
         return 1;
    } else {
        printf(" %s binh thuong\n", ten);
        return 0;
    }
 }

int main(void) {
    CanhBao_t cam_bien_nhiet;
    strcpy(cam_bien_nhiet.ten, "cb_nhiet");
    cam_bien_nhiet.nguong = 100.0f;
    cam_bien_nhiet.kiem_tra = kiem_tra_qua_nong;

    if (cam_bien_nhiet.kiem_tra != NULL) {
        cam_bien_nhiet.kiem_tra(120.0f, cam_bien_nhiet.nguong, cam_bien_nhiet.ten);
    }

    CanhBao_t cam_bien_ap_suat;
    strcpy(cam_bien_ap_suat.ten, "cb_ap_suat");
    cam_bien_ap_suat.nguong = 2.0f;
    cam_bien_ap_suat.kiem_tra = kiem_tra_qua_thap;

    if (cam_bien_ap_suat.kiem_tra != NULL) {
        cam_bien_ap_suat.kiem_tra(4.0f, cam_bien_ap_suat.nguong, cam_bien_ap_suat.ten);
    }
    
    return 0;
}
