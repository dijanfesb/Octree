#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <array>
#include "bounds.hpp"

using namespace std;

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

};

#endif