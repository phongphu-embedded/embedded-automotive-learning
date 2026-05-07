#include <stdio.h>

int main(void) {
    int i = 0;
    float tongtro = 0.0f;
    float r[5] = {100.0f, 220.0f, 330.0f, 470.0f, 680.0f};

    for(i = 0; i < 5; i++)
    {
        tongtro = tongtro + r[i];
    }
    printf("Tong tro: %.2f Ohm\n", tongtro);

    return 0;
}