#include <string.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct cstr_s cstr_t;
struct cstr_s
{

    char *data;
    size_t buf_size;
    size_t data_len;
};
cstr_t *cstr_append(cstr_t *str, const char *s);
cstr_t *cstr_append_size(cstr_t *str, const char *s, size_t len);
void cstr_reset(cstr_t *str);
void  cstr_free(cstr_t *str);
