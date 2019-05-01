#include <stdio.h>
#include <math.h>

// Return 1 if x is prime, else return 0.
int is_prime(int x)
{
    double s;
    int i;
    if (x < 2) {
        return 0;
    }
    if (x == 2) {
        return 1;
    }
    s = sqrt(x);
    if ((int)s == s) {
        return 0;
    }
    for (i = 2; i < s; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int i;
    int num = 0;
    int max = 10000000;

    for (i = 0; i < max; i++) {
        if (is_prime(i)) {
            //printf("%d\t", i);
            num++;
        }
    }

    printf("\n");

    printf("Prime:%d\n", num);
    printf("Total:%d\n", max);
    printf("%.9f\n", (double)num / max);
    return 0;
}
