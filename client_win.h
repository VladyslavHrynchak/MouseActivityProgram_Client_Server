#ifdef  _WIN32
#ifndef CLIENT_WIN_H
#define CLIENT_WIN_H
#include "socket_win.h"

class Client:public Socket
{
public:
    Client();

    void start();

    void getСoordinates_of_mouse(Point &point);

    void getСoordinates_left_right_button_click_of_mouse(Point &left,Point &right);

private:
    sockaddr_in client;

    Point coordinates_of_mouse;

    Point coordinates_of_left_click_of_mouse;

    Point coordinates_of_right_click_of_mouse;
};

#endif
#endif
