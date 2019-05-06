#include "lstmlib.h"

struct lstmlib* lstmlib_create(int length)
{
    struct lstmlib* lstm = malloc(sizeof (struct lstmlib*));
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
    if (!(*lstm).have_error) {
        free((*lstm).x);
    }
    free(lstm);
}
