#ifndef AZ13JS_LSTMLIB

#define AZ13JS_LSTMLIB

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct lstmlib
{
    int length;
    double* x;
    double Wfh;
    double Wfx;
    double bf;
    unsigned char have_error;
    char* error_message;
};

struct lstmlib* lstmlib_create(int length);
char* lstmlib_get_error_message(struct lstmlib* lstm);
void lstmlib_destory(struct lstmlib* lstm);
void lstmlib_printx(struct lstmlib* lstm);
void lstmlib_fillx(struct lstmlib* lstm, double v);
void lstmlib_print_params(struct lstmlib* lstm);

#endif
