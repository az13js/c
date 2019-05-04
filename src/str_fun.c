#include <stdio.h>
#include <math.h>

struct Apple
{
    unsigned char isRead;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Apple createApple(int red, int green, int blue)
{
    struct Apple newApple;
    newApple.isRead = 1;
    newApple.red = red;
    newApple.green = green;
    newApple.blue = blue;
    return newApple;
}

int main(int argc, char *argv[])
{
    struct Apple myApple = createApple(255, 12, 11);
    printf("IsRead:%d,R:%d,G:%d,B:%d\n", myApple.isRead, myApple.red, myApple.green, myApple.blue);
    return 0;
}




