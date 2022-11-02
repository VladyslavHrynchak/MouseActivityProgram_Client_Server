#ifdef  _WIN32
#ifndef SOCKET_WIN_H
#define SOCKET_WIN_H
#include <ws2tcpip.h>
#include <winsock.h>
#include <string>
#include "point.h"

class Socket
{
public:

    Socket();

    void create_socket(const std::string &name_,const std::string &ipAddress_,const int port_);

    std::string name;

    std::string ipAddress;

    int port;

    WSAData wsaData;

    SOCKADDR_IN hint;

    int sizeofhint ;

};

#endif
#endif
