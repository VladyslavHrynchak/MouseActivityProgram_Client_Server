#ifdef  _WIN32
#include "server_win.h"
#include <iostream>

using namespace std;

Server::Server()
{

}

void Server::start()
{
    string name = "Server";
    string ipAddress = "0.0.0.0";
    cout << "Server started....."<< endl;

    create_socket(name,ipAddress,54000);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);

    if(bind(sock, (SOCKADDR*)&hint, sizeof(hint)) == -1)
    {
        cerr << name <<": failed to connect to IP/port" << endl;
       return;
    }

    listen(sock, SOMAXCONN);

    SOCKET client;
    socklen_t client_size = sizeof(client);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    client = accept(sock, (SOCKADDR*)&hint, &sizeofhint);

    if(client == 0)
    {
        cerr << "Server: problem with client connecting" << endl;
    }

    closesocket(sock);

    memset(host,0,NI_MAXHOST);
    memset(service,0,NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,service,NI_MAXSERV,0);

    if(result)
    {
        cout << "Server: " << host << " connected on " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET,&hint.sin_addr,host,NI_MAXHOST);
        cout << "Server: " << host << " connected on " << ntohs(hint.sin_port) << endl;
    }

    char *buff;

    char *buff_l;

    char *buff_r;

    while(true)
    {
        log_file.open_file();
        buff = (char*) &coordinates_of_mouse_recv;
        buff_l = (char*) &coordinates_of_left_click_of_mouse_recv;
        buff_r = (char*) &coordinates_of_right_click_of_mouse_recv;

        int bytesResived = recv(client,buff,sizeof(buff),0);
        int bytesResived_left = recv(client,buff_l,sizeof(buff_l),0);
        int bytesResived_right = recv(client,buff_r,sizeof(buff_r),0);

        if(bytesResived == -1 || bytesResived_left == -1 || bytesResived_right == -1)
        {
            cerr << "There was a connection issue" << endl;
            break;
        }

        if(bytesResived == 0 || bytesResived_left == 0 || bytesResived_right == 0)
        {
            cerr << "Client is disconected" << endl;
            break;
        }

        parse_char_p_to_point((Point*) buff,coordinates_of_mouse_recv);

        parse_char_p_to_point((Point*) buff_l,coordinates_of_left_click_of_mouse_recv);

        parse_char_p_to_point((Point*) buff_r,coordinates_of_right_click_of_mouse_recv);

        log_file.write_right_click_of_mouse(coordinates_of_right_click_of_mouse_recv);
        log_file.write_coordinates_of_mouse(coordinates_of_mouse_recv);
        log_file.write_left_click_of_mouse(coordinates_of_left_click_of_mouse_recv);

    }
    log_file.close_file();
    closesocket(client);

}

void Server::parse_char_p_to_point( Point * buff ,Point &point)
{
    point.x = buff->x;
    point.y = buff->y;
}
#endif
