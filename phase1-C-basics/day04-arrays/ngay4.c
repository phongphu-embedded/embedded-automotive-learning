#include <stdio.h>

int main(void) {
    int i = 0;
    float temp[4] = {72.1f, 73.5f, 80.2f, 79.3f};

    for (i = 0; i < 4; i++) {
        printf("temp[%d] = %1f | dia chi = %p\n",
        i, temp[i], (void*)&temp[i]);
    }
    return 0;
}