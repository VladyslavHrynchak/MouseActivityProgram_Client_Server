#ifndef TEXT_FILE_H
#define TEXT_FILE_H
#include <string>
#include "point.h"
#include <fstream>

class Text_file
{
public:
    Text_file();

    void write_coordinates_of_mouse(const Point& coordinates_of_mouse_recv);

    void write_left_click_of_mouse(const Point &left_click_of_mouse_recv);

    void write_right_click_of_mouse(const Point &right_click_of_mouse_recv);

    void open_file();

    void close_file();
private:
      std::ofstream fw;
      std::string name;
};

#endif
