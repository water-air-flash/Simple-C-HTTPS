#include "chttp_socket.h"

chttp_socket_t chttp_socket()
{
    chttp_socket_t sock = 0;

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStarup(wVersionRequested, &wsaData);

    if (err != 0)
    {
        return 0;
    }
    //LOBYTE macro : Retrieves the low-order byte from the specified value.
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms632658(v=vs.85).aspx
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE())
    {
    }
}
