#ifdef linux
#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
#include "text_file.h"
class Server:public Socket
{
public:
    Server();

    void start();

private:
    Point coordinates_of_mouse_recv;

    Point coordinates_of_left_click_of_mouse_recv;

    Point coordinates_of_right_click_of_mouse_recv;

    Text_file log_file;

};

#endif
#endif
