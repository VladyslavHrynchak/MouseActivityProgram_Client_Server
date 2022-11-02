#ifndef MOUSE_ACTIVITY_PROGRAM_H
#define MOUSE_ACTIVITY_PROGRAM_H

#ifdef linux
#include "socket.h"
#include "server.h"
#include "client.h"

#elif _WIN32
#include "socket_win.h"
#include "server_win.h"
#include "client_win.h"
#endif
class Mouse_activity_program
{
public:
    Mouse_activity_program();

    void start();

    Server server;

    Client client;
};

#endif

