#include "../include/vertex.hpp"
#include "../include/bounds.hpp"

#include <string>
#include <sstream>


using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

Vertex::Vertex(double _x, double  _y, double _z)
{
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

int Vertex::setCoordinates(double _x, double _y, double _z)
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

array <double, 3> Vertex::getCoordinates()
{
    array <double, 3> temp = {x, y, z};
    return temp;
}

bool Vertex::insideBounds(Bounds& bounds)
{
    return (this->x >= bounds.leftX)  &&  (this->x <= bounds.rightX) &&
           (this->y >= bounds.bottomY) && (this->y <= bounds.topY) &&
           (this->z >= bounds.backZ)  &&  (this->z <= bounds.frontZ);
}

QVector3D Vertex::toQVector3D()
{
    return QVector3D(this->x, this->y, this->z);
}

Kernel::Point_3 Vertex::toPoint3()
{
    return Kernel::Point_3(x, y, z);
}