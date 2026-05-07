#include <stdio.h> 

int main(void) {
    int tuoi = 22;
    float gpa = 3.55f;
    char ten = 'P';
    float chieu_cao = 1.75f;
 
    printf("Ten: %c\n", ten);
    printf("Tuoi: %d\n", tuoi);
    printf("GPA: %.2f\n", gpa);
    printf("Chieucao: %.2f\n", chieu_cao);
    printf("Ten: %c - Tuoi: %d - GPA: %.2f", ten, tuoi, gpa);

    return 0;
}

git config --global user.name "Nguyen Phong Phu"
git config --global user.email "phongphu29022004@gmail.com"