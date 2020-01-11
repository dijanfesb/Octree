#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include <array>

#include "vertex.hpp"

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
    bool BoundsCollision(Bounds& b2);
    
};

#endif