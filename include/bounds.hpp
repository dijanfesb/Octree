#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include <array>

#include "vertex.hpp"

typedef array <Vertex *, 3> pTriangle;

using namespace std;
class Bounds {
public:
    double rightX;
    double leftX;
    double topY;
    double bottomY;
    double frontZ;
    double backZ;

    Bounds();
    array <Vertex, 8> getCorners();
    bool intersect(Bounds& b2);
    vector <pTriangle> findTrianglesInside(vector <pTriangle>& triangles);
    bool triangleInside(pTriangle& triangle);
    Vertex findCenter();
    Bounds calculate(const char * octant, Vertex parentsCenter);
    static Bounds find(vector <Vertex> Vertices);

};

#endif