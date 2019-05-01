#include <stdio.h>

int main()
{
    float f_num = 12.2;
    double d_num = 12.2;
    printf("float:%d,double:%d\n", sizeof f_num, sizeof d_num);
    printf("%d,%f\n", sizeof &f_num, *(&f_num));
    return 0;
}

