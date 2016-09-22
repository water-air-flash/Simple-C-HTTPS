#include <winsock2.h>
#include <ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#include "cstr.h";

typedef SOCKET chttp_socket_t;
chttp_socket_t chttp_socket();
chttp_socket_t chttp_socket_connect(chttp_socket_t socket,void *buffer,size_t size,int flags);
int chttp_socket_send(chttp_socket_t socket,void *buffer,size_t size,int flags);
int chttp_socket_recv(chttp_socket_t socket,void *buffer,size_t size,int flags);

cstr_t * chttp_ssl_request(chttp_socket_t socket,void *buffer,size_t size);

void chttp_socket_close(chttp_socket socket);