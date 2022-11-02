#ifdef linux
#include "socket.h"
#include <iostream>

using namespace std;

Socket::Socket()
{

}

void Socket::create_socket(const string &name_,const std::string &ipAddress_,const int port_)
{
    name = name_;
    ipAddress = ipAddress_;
    port = port_;
    sock = socket(AF_INET,SOCK_STREAM,0);

    if(sock == -1)
    {
        cerr << name << ": failed to create socket"<< endl;
    }

    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET,ipAddress.c_str(),&hint.sin_addr);
}
#endif
