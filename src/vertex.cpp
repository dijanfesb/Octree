#include "../include/vertex.hpp"
#include <string>
#include <sstream>

using namespace std;

Vertex::Vertex(double _x, double  _y, double _z)
{
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

int Vertex::set_coordinates(double _x, double _y, double _z)
{
    this->x = _x;
    this->y = _y;
    this->z = _z;

    return 0;
}

Vertex::Vertex(string vLine)
{
    /*
     * FORMAT: v x y z
     */

    istringstream line(vLine);

    char v;

    line >> v;

    line >> x >> y >> z;
}

array <double, 3> Vertex::get_coordinates()
{
    array <double, 3> temp = {x, y, z};
    return temp;
}