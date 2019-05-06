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
    (*lstm).Wfh = (double)rand() / RAND_MAX - 0.5;
    (*lstm).Wfx = (double)rand() / RAND_MAX - 0.5;
    (*lstm).bf = (double)rand() / RAND_MAX - 0.5;
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
