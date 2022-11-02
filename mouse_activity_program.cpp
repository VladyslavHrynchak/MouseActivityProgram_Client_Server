#include "mouse_activity_program.h"
#include <thread>

using namespace std;
Mouse_activity_program::Mouse_activity_program()
{

}

void Mouse_activity_program::start()
{

    thread th1([this]()
    {
        server.start();
    });

    thread th2([this]()
    {
        client.start();
    });

    th1.join();
    th2.join();

}
