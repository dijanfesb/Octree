#include "../include/vertex.hpp"
#include "../include/bounds.hpp"
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

bool Vertex::vertexInsideBounds(Bounds bounds)
{
    bool xIn = (this->x > bounds.leftX) && (this->x < bounds.rightX);
    bool yIn = (this->y > bounds.bottomY) && (this->y < bounds.topY);
    bool zIn = (this->z > bounds.backZ) && (this->z < bounds.frontZ);

    return (xIn && yIn && zIn);
}
