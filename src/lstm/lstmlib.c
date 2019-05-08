#include "lstmlib.h"

struct lstmlib* lstmlib_create(int length)
{
    struct lstmlib* lstm = (struct lstmlib*)malloc(sizeof (struct lstmlib));
    if (length < 1) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "Error, length < 1";
        return lstm;
    }
    (*lstm).x = (double*)calloc(length, sizeof (double));
    if (!(*lstm).x) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        return lstm;
    }
    (*lstm).h = (double*)calloc(length, sizeof (double));
    if (!(*lstm).h) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        return lstm;
    }
    (*lstm).f = (double*)calloc(length, sizeof (double));
    if (!(*lstm).f) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        free((*lstm).h);
        return lstm;
    }
    (*lstm).i = (double*)calloc(length, sizeof (double));
    if (!(*lstm).i) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        free((*lstm).h);
        free((*lstm).f);
        return lstm;
    }
    (*lstm).tilde_c = (double*)calloc(length, sizeof (double));
    if (!(*lstm).tilde_c) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        free((*lstm).h);
        free((*lstm).f);
        free((*lstm).i);
        return lstm;
    }
    (*lstm).c = (double*)calloc(length, sizeof (double));
    if (!(*lstm).c) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        free((*lstm).h);
        free((*lstm).f);
        free((*lstm).i);
        free((*lstm).tilde_c);
        return lstm;
    }
    (*lstm).o = (double*)calloc(length, sizeof (double));
    if (!(*lstm).o) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        free((*lstm).h);
        free((*lstm).f);
        free((*lstm).i);
        free((*lstm).tilde_c);
        free((*lstm).c);
        return lstm;
    }
    (*lstm).hp = (double*)calloc(length, sizeof (double));
    if (!(*lstm).hp) {
        (*lstm).have_error = 1;
        (*lstm).error_message = "calloc() fail.\n";
        free((*lstm).x);
        free((*lstm).h);
        free((*lstm).f);
        free((*lstm).i);
        free((*lstm).tilde_c);
        free((*lstm).c);
        free((*lstm).o);
        return lstm;
    }
    (*lstm).Wfh = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wfx = (double)rand() / RAND_MAX - 0.5;
    (*lstm).bf = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wih = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wix = (double)rand() / RAND_MAX - 0.5;
    (*lstm).bi = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wch = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wcx = (double)rand() / RAND_MAX - 0.5;
    (*lstm).bc = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Woh = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wox = (double)rand() / RAND_MAX - 0.5;
    (*lstm).bo = (double)rand() / RAND_MAX - 0.5;
    (*lstm).length = length;
    (*lstm).have_error = 0;
    (*lstm).error_message = "\n";
    return lstm;
}

char* lstmlib_get_error_message(struct lstmlib* lstm)
{
    return (*lstm).error_message;
}

void lstmlib_destory(struct lstmlib* lstm)
{
    if (lstm) {
        if (!(*lstm).have_error) {
            free((*lstm).x);
            free((*lstm).h);
            free((*lstm).f);
            free((*lstm).i);
            free((*lstm).tilde_c);
            free((*lstm).c);
            free((*lstm).o);
        }
        free(lstm);
    }
}

void lstmlib_printx(struct lstmlib* lstm)
{
    int i;
    if (lstm) {
        if (!(*lstm).have_error) {
            for (i = 0; i < (*lstm).length; i++) {
                printf("%d, %lf\n", (i + 1), (*lstm).x[i]);
            }
        }
    }
}

void lstmlib_fillx(struct lstmlib* lstm, double v)
{
    int i;
    if (lstm) {
        if (!(*lstm).have_error) {
            for (i = 0; i < (*lstm).length; i++) {
                (*lstm).x[i] = v;
            }
        }
    }
}

void lstmlib_print_params(struct lstmlib* lstm)
{
    if (lstm) {
        if (!(*lstm).have_error) {
            printf("Wfh=%lf\n", (*lstm).Wfh);
            printf("Wfx=%lf\n", (*lstm).Wfx);
            printf("bf=%lf\n", (*lstm).bf);
        }
    }
}

void lstmlib_randx(struct lstmlib* lstm)
{
    int i;
    if (lstm) {
        if (!(*lstm).have_error) {
            for (i = 0; i < (*lstm).length; i++) {
                (*lstm).x[i] = (double)rand() / RAND_MAX - 0.5;
            }
        }
    }
}

void lstmlib_run_calc(struct lstmlib* lstm)
{
    int i;
    if (lstm) {
        if (!(*lstm).have_error) {
            for (i = 0; i < (*lstm).length; i++) {
                if (i == 0) {
                    (*lstm).f[i] = 1.0 / (1.0 + exp(-((*lstm).Wfx * (*lstm).x[i] + (*lstm).bf)));
                    (*lstm).i[i] = 1.0 / (1.0 + exp(-((*lstm).Wix * (*lstm).x[i] + (*lstm).bi)));
                    (*lstm).tilde_c[i] = 1.0 / (1.0 + exp(-((*lstm).Wcx * (*lstm).x[i] + (*lstm).bc)));
                    (*lstm).c[i] = (*lstm).i[i] * (*lstm).tilde_c[i];
                    (*lstm).o[i] = 1.0 / (1.0 + exp(-((*lstm).Wox * (*lstm).x[i] + (*lstm).bo)));
                } else {
                    (*lstm).f[i] = 1.0 / (1.0 + exp(-((*lstm).Wfh * (*lstm).h[i - 1] + (*lstm).Wfx * (*lstm).x[i] + (*lstm).bf)));
                    (*lstm).i[i] = 1.0 / (1.0 + exp(-((*lstm).Wih * (*lstm).h[i - 1] + (*lstm).Wix * (*lstm).x[i] + (*lstm).bi)));
                    (*lstm).tilde_c[i] = 1.0 / (1.0 + exp(-((*lstm).Wch * (*lstm).h[i - 1] + (*lstm).Wcx * (*lstm).x[i] + (*lstm).bc)));
                    (*lstm).c[i] = (*lstm).f[i] * (*lstm).c[i - 1] + (*lstm).i[i] * (*lstm).tilde_c[i];
                    (*lstm).o[i] = 1.0 / (1.0 + exp(-((*lstm).Woh * (*lstm).h[i - 1] + (*lstm).Wox * (*lstm).x[i] + (*lstm).bo)));
                }
                (*lstm).h[i] = (*lstm).o[i] * tanh((*lstm).c[i]);
            }
        }
    }
}

void lstmlib_print_h(struct lstmlib* lstm)
{
    int i;
    if (lstm) {
        if (!(*lstm).have_error) {
            printf("t,x,forgetgate,inputgate,tilde_c,c,outputgate,h\n");
            for (i = 0; i < (*lstm).length; i++) {
                printf("%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", (i + 1), (*lstm).x[i], (*lstm).f[i], (*lstm).i[i], (*lstm).tilde_c[i], (*lstm).c[i], (*lstm).o[i], (*lstm).h[i]);
            }
        }
    }
}

void lstmlib_set_hp(struct lstmlib* lstm)
{
    int i;
    if (lstm) {
        if (!(*lstm).have_error) {
            printf("Call lstmlib_set_hp:\n");
            for (i = 0; i < (*lstm).length; i++) {
                (*lstm).hp[i] = (double)rand() / RAND_MAX - 0.5;
                printf("  hp[%d]=%lf\n", (i + 1), (*lstm).hp[i]);
            }
            printf("print hp finish.\n");
        }
    }
}

void lstmlib_calc_d(struct lstmlib* lstm)
{
    if (lstm) {
        if (!(*lstm).have_error) {
            printf("Call latmlib_calc_d:\n");
        }
    }
}

void lstmlib_print_d(struct lstmlib* lstm)
{
    if (lstm) {
        if (!(*lstm).have_error) {
            printf("Call lstmlib_print_d:\n");
        }
    }
}
