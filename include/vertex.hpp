#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <array>
#include <QVector3D>

#include <CGAL/Point_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

class Bounds;
class Vertex
{
    private:
        double x;
        double y;
        double z;
    public:
        Vertex(string vLine);
        array <double, 3> getCoordinates();
        Vertex(double _x = 0, double  _y = 0, double _z = 0);
        int setCoordinates(double _x, double _y, double _z);
        bool insideBounds(Bounds& bounds);
        QVector3D toQVector3D();
        Kernel::Point_3 toPoint3();

        static bool compare_x(const Vertex& v1, const Vertex& v2);
        static bool compare_y(const Vertex& v1, const Vertex& v2);
        static bool compare_z(const Vertex& v1, const Vertex& v2);
};

#endif