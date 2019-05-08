#ifndef AZ13JS_LSTMLIB

#define AZ13JS_LSTMLIB

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct lstmlib
{
    int length;
    double* x;
    double* h;
    double* f; // 遗忘门的输出
    double* i; // 输入门的输出
    double* tilde_c; // 中间变量
    double* c; // 状态参数C
    double* o; // 输出门的输出
    double* hp; // 期望输出值
    double Wfh;
    double Wfx;
    double bf;
    double Wih;
    double Wix;
    double bi;
    double Wch;
    double Wcx;
    double bc;
    double Woh;
    double Wox;
    double bo;
    unsigned char have_error;
    char* error_message;
};

struct lstmlib* lstmlib_create(int length);
char* lstmlib_get_error_message(struct lstmlib* lstm);
void lstmlib_destory(struct lstmlib* lstm);
void lstmlib_printx(struct lstmlib* lstm);
void lstmlib_fillx(struct lstmlib* lstm, double v);
void lstmlib_print_params(struct lstmlib* lstm);
void lstmlib_randx(struct lstmlib* lstm);
void lstmlib_run_calc(struct lstmlib* lstm);
void lstmlib_print_h(struct lstmlib* lstm);
void lstmlib_set_hp(struct lstmlib* lstm);
void lstmlib_calc_d(struct lstmlib* lstm);
void lstmlib_print_d(struct lstmlib* lstm);

#endif
