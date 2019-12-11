#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>

using namespace std;

class Vertex
{
    private:
        double x;
        double y;
        double z;
    public:
        Vertex(string vLine);
        Vertex(double _x = 0, double  _y = 0, double _z = 0);
        int set_coordinates(double _x, double _y, double _z);
};

#endif