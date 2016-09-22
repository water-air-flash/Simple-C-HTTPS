#include "chttp_socket.h"
/***=============***/

/***=============***/

/***=============***/

/***=============***/

int main()
{

    chttp_socket_t socket = chttp_socket();
    chttp_socket_connect(socket, "baidu.com", 80);

    chttp_ssl_request(socket,"123",)
}
/*
    cstr_t *str = NULL;
    str = cstr_append(str, "Hello");
    printf("%s", str->data);
*/

//gcc main.c cstr.c chttp_socket.c -o m.exe -Wall -lws2_32