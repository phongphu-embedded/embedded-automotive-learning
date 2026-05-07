#include <stdio.h>

int main(void) {

    float speed = 92.0f;
    int troi_mua = 1;

    if(speed <= 60.0f)
    {
        printf("An toan\n");
    }
    else if (speed <=90.0f)
    {
        printf("Canh bao:giam toc\n");
    }
    else
    {
        printf("NGUY HIEM\n");
    if(troi_mua) {
        printf("Nguy co truot banh\n");
    } }
    return 0;
}