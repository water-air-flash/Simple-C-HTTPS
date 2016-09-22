
#include "cstr.h"
cstr_t *cstr_append(cstr_t *str, const char *s)
{
    if ((s != NULL && s[0] != 0))
    {

        return cstr_append_size(str, s, strlen(s));
    }
    else
    {
        return str;
    }
}
cstr_t *cstr_append_size(cstr_t *str, const char *s, size_t len)
{
    if (str == NULL)
    {
        str = (cstr_t *)malloc(sizeof(cstr_t));
        memset(str, 0, sizeof(cstr_t));
        str->data_len = len;
        str->buf_size = str->data_len << 2;
        str->data = malloc(str->buf_size);
        memset(str->data, 0, str->buf_size);
        memcpy(str->data, s, str->data_len);
        return str;
    }
    if (str->buf_size - str->data_len < len)
    {
        char *temp = NULL;
        do
        {
            temp = realloc(str->data, str->buf_size + (len << 2));
        } while (!temp);

        str->data = temp;
        str->buf_size += len << 2;
    }
    memcpy(str->data + str->data_len, s, len);
    str->data_len += len;
    return str;
}
void cstr_reset(cstr_t *str)
{
    str->data_len = 0;
    memset(str->data, 0, str->buf_size);
}
void cstr_free(cstr_t *str)
{
    if (str)
    {
        if (str->data)
        {
            free(str->data);
        }
        free(str);
    }
}