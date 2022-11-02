#ifdef  _WIN32
#ifndef SERVER_WIN_H
#define SERVER_WIN_H
#include "socket_win.h"
#include "text_file.h"
class Server:public Socket
{
public:
    Server();

    void start();

private:
    void parse_char_p_to_point( Point * buff ,Point &point);

    Point coordinates_of_mouse_recv;

    Point coordinates_of_left_click_of_mouse_recv;

    Point coordinates_of_right_click_of_mouse_recv;

    Text_file log_file;

};

#endif
#endif
