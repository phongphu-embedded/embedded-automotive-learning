#include <stdio.h>

int main(void) {
    int i = 0;
    int flag_rpm_cao = 0;
    int canhbao3000 = 0;
    float tong = 0.0f;
    float rpm[10] = {
        800.0f, 1200.0f, 2500.0f, 3800.0f, 4200.0f,
    3500.0f, 2800.0f, 1500.0f, 900.0f, 850.0f};
    float rpm_max = rpm[0];

    for (i = 0; i < 10; i++) {
        printf("Chu ky %d: %.2f RPM\n", i+ 1 , rpm[i]);
        tong = tong + rpm[i];
        if (rpm[i] > rpm_max) {
            rpm_max = rpm[i];
        }
        if (rpm[i] > 3000.0f) {
            canhbao3000++;
        }
        if ((rpm[i] > 4000.0f) && (flag_rpm_cao == 0)) {
        printf("CANHBAO: RPM qua cao!\n");
        flag_rpm_cao = 1;
        }
        }
    printf("Toc do trung binh %.2f RPM\n", tong/10);
    printf("RPM cao nhat: %.2f RPM\n", rpm_max);
    printf("Solanvuotqua3000: %d lan\n", canhbao3000);
    
    return 0;
    }