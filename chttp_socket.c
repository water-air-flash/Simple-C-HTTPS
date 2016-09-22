#include "chttp_socket.h"

chttp_socket_t chttp_socket()
{
    chttp_socket_t sock = 0;

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);
    // WSAStartup function : The WSAStartup function initiates use of the Winsock DLL by a process.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms742213(v=vs.85).aspx
    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0)
    {
        printf("WSAStartup Failed: %d\n", err);
        return 0;
    }
    //LOBYTE macro : Retrieves the low-order byte from the specified value.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms632658(v=vs.85).aspx
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
    {
        WSACleanup();
        return 0;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
        return 0;
    return sock;
}

chttp_socket_t chttp_socket_connect(chttp_socket_t sock, const char *host, int port)
{
    struct hostent *phost;
    struct sockaddr_in addr;
    int rc = 0;
    phost = gethostbyname(host);

    if (phost == NULL)
    {
        DWORD dwError = WSAGetLastError();
        if (dwError != 0)
        {
            if (dwError == WSAHOST_NOT_FOUND)
            {
                printf("Host not found\n");
                return 0;
            }
            else if (dwError == WSANO_DATA)
            {
                printf("No data record found\n");
                return 0;
            }
            else
            {
                printf("Function failed with error: %ld\n", dwError);
                return 0;
            }
        }
        return 0;
    }
    else
    {
        printf("\tOfficial name: %s\n", phost->h_name);
        int i = 0;
        char **pAlias;
        for (pAlias = phost->h_aliases; *pAlias != 0; pAlias++)
        {
            printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
        }
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *((unsigned long *)phost->h_addr_list[0]);

    rc = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (0 != rc)
    {
        printf("connect %s failed.\n", host);
        return 0;
    }
    return sock;
}

int chttp_socket_send(chttp_socket_t socket, void *buffer, size_t size, int flags)
{
    return send(socket, buffer, size, flags);
}
int chttp_socket_recv(chttp_socket_t socket, void *buffer, size_t size, int flags)
{
    return recv(socket, buffer, size, flags);
}

cstr_t *chttp_ssl_request(chttp_socket_t socket, void *buffer, size_t size)
{
    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;
    int ret = 0;
    char text[1024];
    cstr_t *data = NULL;

    SSL_library_init();
    SSL_load_error_strings();

    ctx = SSL_CTX_new(SSLv23_client_method());

    if (ctx == NULL)
    {
        printf("SSL_CTX_new failed\n");
        return NULL;
    }
    ssl = SSL_new(ctx);

    if (NULL == ssl)
    {
        printf("SSL_new failed\n");
        return NULL;
    }
    ret = SSL_set_fd(ssl, socket);
    if (0 == ret)
    {
        printf("SSL_set_fd failed\n");
        return NULL;
    }

    RAND_poll();
    while (RAND_status() == 0)
    {
        unsigned short rand_ret = rand() % 65536;
        RAND_seed(&rand_ret, sizeof(rand_ret));
    }
    ret = SSL_connect(ssl);
    if (ret != 1)
        return NULL;

    if (!(SSL_write(ssl, buffer, size)))
    {
        return NULL;
    }

    while ((ret = SSL_read(ssl, text, 1024)) > 0)
    {
        data = cstr_append_size(data, text, ret);
    }

    //free resource
    if (ssl)
    {
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        ERR_free_strings();
    }

    return data;
}