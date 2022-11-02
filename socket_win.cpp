#ifdef  _WIN32
#include "socket_win.h"
#include <iostream>

using namespace std;

Socket::Socket()
{

}

void Socket::create_socket(const string &name_,const string &ipAddress_,const int port_)
{
    name = name_;
    ipAddress = ipAddress_;
    port = port_;

    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "Error" << endl;
        exit(1);
    }

    sizeofhint = sizeof(hint);
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.s_addr = inet_addr(ipAddress.c_str());
}
#endif
