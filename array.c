#include <stdio.h>

int main()
{
    int a[20];
    int i;

    printf("sizeof a:%d\n", sizeof a);

    for (i = 0; i < 20; i++) {
        a[i] = i;
    }
    for (i = 0; i < 20; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
    return 0;
}
