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
    return (this->x >= bounds.leftX)  &&  (this->x <= bounds.rightX) &&
           (this->y >= bounds.bottomY) && (this->y <= bounds.topY) &&
           (this->z >= bounds.backZ)  &&  (this->z <= bounds.frontZ);
}

QVector3D Vertex::toQVector3D()
{
    return QVector3D(this->x, this->y, this->z);
}

Vertex Vertex::operator - (Vertex v2) 
{
    return Vertex(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

Vertex Vertex::operator + (Vertex v2)
{
    return Vertex(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

double Vertex::operator * (Vertex v2) // Skalarni produkt
{
    return this->x * v2.x + this->y * v2.y + this->z * v2.z;
}

Vertex Vertex::operator & (Vertex v2) // Vektorski produkt
{
    double x = this->y*v2.z - v2.y*this->z;
    double y = v2.x*this->z - this->x*v2.z;
    double z = this->x*v2.y - v2.x*this->y;

    return Vertex(x, y, z);
}