#ifdef linux
#ifndef SOCKET_H
#define SOCKET_H
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include "point.h"

class Socket
{
public:

    Socket();

    std::string name;

    void create_socket(const std::string &name_,const std::string &ipAddress_,const int port_);

    int sock;

    std::string ipAddress;

    int port;

    sockaddr_in hint;

};

#endif
#endif
