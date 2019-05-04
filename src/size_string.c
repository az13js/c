#include <stdio.h>

int main()
{
    char a[3] = {'A', 'B'};
    char *b;

    printf("->%s<-\n", a);

    printf("size:%d\n", sizeof a);
    printf("sizeof *b:%d\n", sizeof b);
    return 0;
}

