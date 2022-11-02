#ifdef linux
#include "client.h"
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

using std::this_thread::sleep_for;

using namespace std;

Client::Client()
{

}

void Client::getСoordinates_of_mouse(Point & point)
{
    Display *display;
    int screen_number;
    unsigned int modbut;

    int x, y,temp;
    if ( ( display = XOpenDisplay ( NULL ) ) == NULL )
    {
        cout << "Can not connect to the X server!"<< endl;
        exit (EXIT_FAILURE);
    }
    screen_number = DefaultScreen ( display );
    Window w = XRootWindow( display, screen_number );
    Window w1;

    XQueryPointer(display, w, &w1, &w1, &x, &y, &temp, &temp, &modbut);
    point.x = x;
    point.y = y;

}

void Client::getСoordinates_left_right_button_click_of_mouse(Point &left,Point &right)
{

    XEvent event;
    Display *display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        cout << "Can not connect to the X server!"<< endl;
        exit (EXIT_FAILURE);
    }
    Window root= XDefaultRootWindow(display);
    XGrabPointer(display, root, False, ButtonPressMask, GrabModeAsync,GrabModeAsync, None, None, CurrentTime);
    XSelectInput(display, root, ButtonPressMask);

    XNextEvent(display,&event);
    switch(event.type){
    case ButtonPress:
        switch(event.xbutton.button)
        {
            case Button1:
            left.x =event.xbutton.x;
            left.y = event.xbutton.y;
            break;

            case Button3:
            right.x = event.xbutton.x;
            right.y = event.xbutton.y;
            break;

            default:
            break;

        }
    break;
    default:
        break;
    }

    XCloseDisplay(display);
}

void Client::start()
{
    string name = "Client";
    string ipAddress = "127.0.0.1";

    create_socket(name,ipAddress,54000);

    int connectRes = connect(sock,(sockaddr*)&hint,sizeof(hint));

    while(connectRes == -1)
    {
        cerr << "Client: failed to connect to server"<< endl;
        connectRes = connect(sock,(sockaddr*)&hint,sizeof(hint));
    }
    do
    {
        sleep_for(500ms);

        getСoordinates_of_mouse(coordinates_of_mouse);
        getСoordinates_left_right_button_click_of_mouse(coordinates_of_left_click_of_mouse,coordinates_of_right_click_of_mouse);

        send(sock, &coordinates_of_mouse, sizeof(coordinates_of_mouse),0);

        send(sock, &coordinates_of_left_click_of_mouse, sizeof(coordinates_of_left_click_of_mouse),0);

        send(sock, &coordinates_of_right_click_of_mouse, sizeof(coordinates_of_right_click_of_mouse),0);

    }while(true);

    close(sock);
}
#endif
