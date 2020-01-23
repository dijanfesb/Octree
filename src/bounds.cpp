#include "../include/bounds.hpp"

using namespace std;

Bounds::Bounds()
{
	topY = bottomY = leftX = rightX = frontZ = backZ = 0;
}

array <Vertex, 8> Bounds::getCorners()
{
	array <Vertex, 8> corners;

	corners[0] = Vertex(this->leftX, this->bottomY, this->backZ);
    corners[1] = Vertex(this->leftX, this->bottomY, this->frontZ);
    corners[2] = Vertex(this->leftX, this->topY, this->backZ);
    corners[3] = Vertex(this->leftX, this->topY, this->frontZ);
    corners[4] = Vertex(this->rightX, this->bottomY, this->backZ);
    corners[5] = Vertex(this->rightX, this->bottomY, this->frontZ);
    corners[6] = Vertex(this->rightX, this->topY, this->backZ);
    corners[7] = Vertex(this->rightX, this->topY, this->frontZ);

	return corners;
}

bool Bounds::intersect(Bounds& b2)
{
    array <Vertex, 8> points1 = this->getCorners();
    array <Vertex, 8> points2 = b2.getCorners();

    for (auto vertex : points1)
        if (vertex.insideBounds(b2))
            return true;

    for (auto vertex : points2)
        if (vertex.insideBounds(*this))
            return true;

    return false;
}

vector <pTriangle> Bounds::findTrianglesInside(vector <pTriangle>& triangles)
{
    vector <pTriangle> retVector;

    for (auto triangle : triangles)
        if (this->triangleInside(triangle))
            retVector.push_back(triangle);

    return retVector;
}

bool Bounds::triangleInside(pTriangle& triangle)
{
    for (auto vertex : triangle)
        if (vertex->insideBounds(*this))
            return true;

    return false;
}

Vertex Bounds::findCenter() {
    double x = (this->leftX + this->rightX)/2;
    double y = (this->topY + this->bottomY)/2;
    double z = (this->frontZ + this->backZ)/2;

    return Vertex(x, y, z);
}

Bounds Bounds::calculate(const char * octant, Vertex parentsCenter)
{
    // string Octant : [T/B][F/R][R/L]

    Bounds bounds{};

    if (octant[0] == 'T') {
        bounds.topY = this->topY;
        bounds.bottomY = parentsCenter.getCoordinates()[1];
    }
    else if (octant[0] == 'B') {
        bounds.topY = parentsCenter.getCoordinates()[1];
        bounds.bottomY = this->bottomY;
    }

    if (octant[1] == 'F') {
        bounds.frontZ = this->frontZ;
        bounds.backZ = parentsCenter.getCoordinates()[2];
    }
    else if (octant[1] == 'R') {
        bounds.frontZ = parentsCenter.getCoordinates()[2];
        bounds.backZ = this->backZ;
    }

    if (octant[2] == 'R') {
        bounds.rightX = this->rightX;
        bounds.leftX = parentsCenter.getCoordinates()[0];
    }
    else if (octant[2] == 'L') {
        bounds.rightX = parentsCenter.getCoordinates()[0];
        bounds.leftX = this->leftX;
    }

    return bounds;
}

Bounds Bounds::find(vector <Vertex> Vertices)
{
    Bounds bounds;

    bounds.leftX = (*min_element(Vertices.begin()+1, Vertices.end(), Vertex::compare_x)).getCoordinates()[0];
    bounds.rightX = (*max_element(Vertices.begin()+1, Vertices.end(), Vertex::compare_x)).getCoordinates()[0];
    bounds.bottomY = (*min_element(Vertices.begin()+1, Vertices.end(), Vertex::compare_y)).getCoordinates()[1];
    bounds.topY = (*max_element(Vertices.begin()+1, Vertices.end(), Vertex::compare_y)).getCoordinates()[1];
    bounds.backZ = (*min_element(Vertices.begin()+1, Vertices.end(), Vertex::compare_z)).getCoordinates()[2];
    bounds.frontZ = (*max_element(Vertices.begin()+1, Vertices.end(), Vertex::compare_z)).getCoordinates()[2];

    return bounds;
}