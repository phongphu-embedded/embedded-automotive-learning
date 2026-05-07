#include <stdio.h>

int main(void) {
    float nhiet_do[6] = {72.0f, 78.0f, 86.0f, 91.0f, 83.0f, 79.0f};  /* do C */
    float dien_ap[6] = {12.6f, 12.4f, 11.3f, 11.0f, 12.1f, 12.5f};  /* Volt */
    int rpm[6]  = {800, 1500, 3200, 4500, 2800, 1200};           /* RPM  */
    int i = 0;
    /*nd: nhiet do*/
    /*da: dien ap*/
    /*tb: trung binh*/
    float ndtb = 0.0f; 
    float ndmin = nhiet_do[0];
    float ndmax = nhiet_do[0];
    float datb = 0.0f;
    float damin = dien_ap[0];
    float damax = dien_ap[0];
    float rpmtb = 0.0f;
    float rpmmin = rpm[0];
    float rpmmax = rpm[0];
    int canhbao = 0;

    for (i = 0; i < 6; i++) {
        printf(" [Chu ky %d] Nhiet do: %.2f C | Dien ap: %.2f V | RPM: %d\n", i + 1, nhiet_do[i], dien_ap[i], rpm[i]);
        if (nhiet_do[i] > 85.0f) {
            printf(" >> CANH BAO: Qua nhiet!\n");
            canhbao++;
            }
        if (dien_ap[i] < 11.5f) {
            printf(" >> CANH BAO: Acquy yeu!\n");
            canhbao++;
            }
        if (rpm[i] > 4000) {
            printf(" >> CANH BAO: RPM cao!\n");
            canhbao++;
            }

        ndtb = ndtb + nhiet_do[i];
        datb = datb + dien_ap[i];
        rpmtb = rpmtb + rpm[i];

        if (nhiet_do[i] < ndmin) {
            ndmin = nhiet_do[i];
           }
        if (nhiet_do[i] > ndmax) {
            ndmax = nhiet_do[i];
           }
        if (dien_ap[i] < damin) {
            damin = dien_ap[i];
           }
        if (dien_ap[i] > damax) {
            damax = dien_ap[i];
           }
        if (rpm[i] < rpmmin ) {
            rpmmin = rpm[i];
           }
        if (rpm[i] > rpmmax ) {
            rpmmax = rpm[i];
           }
    }
    printf("--- THONG KE ---\n");
    printf("Nhiet do: TB = %.2f | Min = %.2f | Max = %.2f\n", ndtb/6.0f, ndmin, ndmax);
    printf("Dien ap : TB = %.2f | Min = %.2f | Max = %.2f\n", datb/6.0f, damin, damax);
    printf("RPM     : TB = %.0f | Min = %.0f | Max = %.0f\n", rpmtb/6.0f, rpmmin, rpmmax);
    printf("So canh bao: %d lan\n", canhbao);

    if (canhbao == 0) {
        printf("HE THONG: Binh thuong\n");
        }
    else if (canhbao == 1 || canhbao == 2) {
        printf("HE THONG: Can kiem tra\n");
        }
        else {
            printf("HE THONG: NGUY HIEM - Dung xe ngay!\n");
             }
    return 0;
}