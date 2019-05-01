#include <stdio.h>

struct humans {
    int age;
    int iq;
    float weight;
    char *name;
};

int main()
{
    char name[5] = {'1', '2', '3', '4', '\0'};
    struct humans a;
    a.age = 20;
    a.iq = 100;
    a.weight = 55.2;
    a.name = name;

    printf("Age:%d,IQ:%d,Weight:%f,Name:%s\n", a.age, a.iq, a.weight, a.name);
    return 0;
}

