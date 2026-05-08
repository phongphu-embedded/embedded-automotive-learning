#include <stdio.h>

void tang_gap_doi(float *x) {
    *x = *x * 2.0f;
}

int main(void) {
    float nhiet_do = 36.5f;

    tang_gap_doi(&nhiet_do);
    printf("%.2f\n", nhiet_do);

    return 0;
}