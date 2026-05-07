#include <stdio.h>

int main(void) 
{
    int dem = 10;

    printf("ECU khoi dong...\n");
    while (dem >= 0) {
        printf("T-%d\n", dem);
        dem = dem-2;
    }
    printf("ECU san sang!\n");
    return 0;
}