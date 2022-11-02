#include "text_file.h"
#include <iostream>
#include <fstream>

using namespace std;

Text_file::Text_file():name("log.txt")
{

}

void Text_file::write_coordinates_of_mouse(const Point& coordinates_of_mouse_recv)
{

    if (fw.is_open())
    {


        fw << coordinates_of_mouse_recv.x << "x" << coordinates_of_mouse_recv.y << endl;


    }
    else cout << "Problem with opening file";

}

void Text_file::write_left_click_of_mouse(const Point &left_click_of_mouse_recv)
{
    if (fw.is_open())
    {

        fw << left_click_of_mouse_recv.x<<"x"<<left_click_of_mouse_recv.y<<" LMK (Left Mouse click)" << endl;

    }
    else cout << "Problem with opening file";
}

void Text_file::write_right_click_of_mouse(const Point &right_click_of_mouse_recv)
{
    fw << right_click_of_mouse_recv.x<<"x"<<right_click_of_mouse_recv.y<<" RMK (Right Mouse click)" << endl;
}

void Text_file::open_file()
{
    fw.open(name, std::ofstream::out);

}

void Text_file::close_file()
{
    fw.close();
}
