#ifdef linux
#include "server.h"
#include <iostream>
#include <fstream>

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

    if(bind(sock,(sockaddr*)&hint,sizeof(hint)) == -1)
    {
        cerr << name <<": failed to connect to IP/port" << endl;
       return;
    }

    if(listen(sock,SOMAXCONN) == -1)
    {
        cerr << "Server: failed to listening to IP/port" << endl;
        return;
    }

    sockaddr_in client;
    socklen_t client_size = sizeof(client);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    int client_socket = accept(sock,(sockaddr*)&client,&client_size);

    if(client_socket == -1)
    {
        cerr << "Server: problem with client connecting" << endl;
    }

    close(sock);

    memset(host,0,NI_MAXHOST);
    memset(service,0,NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,service,NI_MAXSERV,0);


    if(result)
    {
        cout << "Server: " << host << " connected on " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);
        cout << "Server: " << host << " connected on " << ntohs(client.sin_port) << endl;
    }


    while(true)
    {
       log_file.open_file();
        int bytesResived = recv(client_socket,&coordinates_of_mouse_recv,sizeof(Point),0);

        int bytesResived_left = recv(client_socket,&coordinates_of_left_click_of_mouse_recv,sizeof(Point),0);

        int bytesResived_right = recv(client_socket,&coordinates_of_right_click_of_mouse_recv,sizeof(Point),0);

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


        log_file.write_right_click_of_mouse(coordinates_of_right_click_of_mouse_recv);
        log_file.write_coordinates_of_mouse(coordinates_of_mouse_recv);
        log_file.write_left_click_of_mouse(coordinates_of_left_click_of_mouse_recv);

    }
    log_file.close_file();
    close(client_socket);

}
#endif
