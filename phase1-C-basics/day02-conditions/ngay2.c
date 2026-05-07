#include <stdio.h> 

int main(void) {
    float diem = 2.0f;

    if (diem >= 8.0f) {
        printf("Gioi!\n");         
    }
    else if (diem >= 6.5f) {
        printf("Kha\n");
    } else if (diem >= 5.0f) {
        printf("Trungbinh\n");
    } else if (diem >= 4.0f) {
        printf("Thi lai\n");
    } else {printf("Rot mon\n");}
return 0; 
}