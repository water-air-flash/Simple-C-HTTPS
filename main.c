#include "cstr.h"
/***=============***/

/***=============***/

/***=============***/

/***=============***/


int main()
{
    
    cstr_t *str = NULL;
    str = cstr_append(str, "Hello");
    printf("%s", str->data);
    return 0;
}
/*
    cstr_t *str = NULL;
    str = cstr_append(str, "Hello");
    printf("%s", str->data);
*/

    //gcc main.c cstr.c -o m.exe