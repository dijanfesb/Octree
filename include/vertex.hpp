#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <array>
#include <QVector3D>

using namespace std;

class Bounds;
class Vertex
{
    private:
        double x;
        double y;
        double z;
    public:
        Vertex(string vLine);
        array <double, 3> get_coordinates();
        Vertex(double _x = 0, double  _y = 0, double _z = 0);
        int set_coordinates(double _x, double _y, double _z);
        bool vertexInsideBounds(Bounds bounds);
        QVector3D toQVector3D();

        Vertex operator - (Vertex v2); 
        Vertex operator + (Vertex v2);
        double operator * (Vertex v2); // Skalarni produkt
        Vertex operator & (Vertex v2); // Vektorski produkt
};

#endif