#include <stdio.h>

int main()
{
    char a;
    char * b;
    int c = 2333;
    int* d;
    d = &c;
    printf("sizeof a:%d, sizeof b:%d\n", sizeof a, sizeof b);
    printf("c=%d,d=%d\n", c, d);
    printf("*d=%d\n", *d);
    return 0;
}
