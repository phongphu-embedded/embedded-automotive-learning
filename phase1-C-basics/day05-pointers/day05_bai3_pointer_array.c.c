#include <stdio.h>

int main(void) {
    float sensor[4] = {72.1f, 73.5f, 80.2f, 79.3f};
    float *p = sensor; /* ten mang = dia chi phan tu dau tien */
    int i = 0;

    for (i = 0; i < 4; i++) {
        printf("sensor[%d] = %.1f | *(p+%d) = %.1f\n",
        i, sensor[i], i, *(p + i));
        }

        return 0;
}

