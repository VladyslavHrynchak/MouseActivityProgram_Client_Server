#ifdef  _WIN32
#include "client_win.h"
#include <iostream>
#include <windows.h>
#include <thread>

using std::this_thread::sleep_for;

using namespace std;

Client::Client()
{

}

void Client::getСoordinates_of_mouse(Point & point)
{
    HWND console_wnd = GetConsoleWindow();
    POINT cursor_pos;

    if (GetCursorPos(&cursor_pos))
    {
        if (console_wnd && ScreenToClient(console_wnd, &cursor_pos));
        {
            point.x = cursor_pos.x;
            point.y = cursor_pos.y;
        }
    }
}

void Client::getСoordinates_left_right_button_click_of_mouse(Point &left,Point &right)
{  

        if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
        {
            getСoordinates_of_mouse(left);
        }

        if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
        {
            getСoordinates_of_mouse(right);
        }    

}

void Client::start()
{
    string name = "Client";
    string ipAddress = "127.0.0.1";

    create_socket(name,ipAddress,54000);

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    int connectRes = connect(Connection,(SOCKADDR*)&hint,sizeof(hint));

    while(connectRes == -1)
    {
        cerr << "Client: failed to connect to server"<< endl;
        connectRes = connect(Connection,(sockaddr*)&hint,sizeof(hint));
    }
    do
    {
        sleep_for(500ms);

        getСoordinates_of_mouse(coordinates_of_mouse);
        getСoordinates_left_right_button_click_of_mouse(coordinates_of_left_click_of_mouse,coordinates_of_right_click_of_mouse);

        send(Connection, (char*)&coordinates_of_mouse, sizeof(coordinates_of_mouse),0);

        send(Connection, (char*)&coordinates_of_left_click_of_mouse, sizeof(coordinates_of_left_click_of_mouse),0);

        send(Connection, (char*)&coordinates_of_right_click_of_mouse, sizeof(coordinates_of_right_click_of_mouse),0);

    }while(true);

    closesocket(Connection);
}
#endif
