#include "../include/octree.hpp"
#include "../include/vertex.hpp"
#include "../include/bounds.hpp"
#include <algorithm>
#include <string>
#include <array>
#include <iostream>

using namespace std;


Bounds findBounds(vector <Vertex> Vertices)
{
    Bounds bounds;

    bounds.topY = (*max_element(Vertices.begin(), Vertices.end(), compare_y)).get_coordinates()[1];
    bounds.bottomY = (*min_element(Vertices.begin(), Vertices.end(), compare_y)).get_coordinates()[1];
    bounds.leftX = (*min_element(Vertices.begin(), Vertices.end(), compare_x)).get_coordinates()[0];
    bounds.rightX = (*max_element(Vertices.begin(), Vertices.end(), compare_x)).get_coordinates()[0];
    bounds.frontZ = (*max_element(Vertices.begin(), Vertices.end(), compare_z)).get_coordinates()[2];
    bounds.backZ = (*min_element(Vertices.begin(), Vertices.end(), compare_z)).get_coordinates()[2];

    return bounds;
}

Vertex findCenter(Bounds bounds) {
    Vertex center;

    double x = (bounds.leftX + bounds.rightX)/2;
    double y = (bounds.topY + bounds.bottomY)/2;
    double z = (bounds.frontZ + bounds.backZ)/2;

    center.set_coordinates(x, y, z);
    return center;
}

vector <Vertex> findVerticesInsideBounds(vector <Vertex> vertices, Bounds bounds)
{
    vector <Vertex> insideVertices;

    for (auto vertex : vertices) {
        if (vertex.vertexInsideBounds(bounds))
            insideVertices.push_back(vertex);
    }

    return insideVertices;
}


bool compare_x(const Vertex& v1, const Vertex& v2) {
    return Vertex(v1).get_coordinates()[0] < Vertex(v2).get_coordinates()[0];
}

bool compare_y(const Vertex& v1, const Vertex& v2) {
    return Vertex(v1).get_coordinates()[1] < Vertex(v2).get_coordinates()[1];
}

bool compare_z(const Vertex& v1, const Vertex& v2) {
    return Vertex(v1).get_coordinates()[2] < Vertex(v2).get_coordinates()[2];
}

Octree::Octree(vector <Vertex> Vertices)
{
    this->Vertices = Vertices;
    level = 0;
    this->bounds = findBounds(Vertices);
    this->center = findCenter(bounds);

    string octants[8] = {"TFR", "TFL", "TBL", "TBR", "BFR", "BFL", "BBL", "BBR"};

    for (int i = 0; i < 8; i++) {
        Children[i] = new Octree(this->Vertices, calculateBounds(octants[i], this->bounds, this->center), level);
    }
}

Bounds calculateBounds(string octant, Bounds parentBounds, Vertex parentsCenter)
{   //                      0           1          2
    // string Octant :    [T/B]       [F/B]      [L/R]
    //                 TOP/BOTTOM  FRONT/BACK  LEFT/RIGHT

    Bounds bounds{};

    if (octant[0] == 'T') {
        bounds.topY = parentBounds.topY;
        bounds.bottomY = parentsCenter.get_coordinates()[1];
    }
    else if (octant[0] == 'B') {
        bounds.topY = parentsCenter.get_coordinates()[1];
        bounds.bottomY = parentBounds.bottomY;
    }

    if (octant[1] == 'F') {
        bounds.frontZ = parentBounds.frontZ;
        bounds.backZ = parentsCenter.get_coordinates()[2];
    }
    else if (octant[1] == 'B') {
        bounds.frontZ = parentsCenter.get_coordinates()[2];
        bounds.backZ = parentBounds.backZ;
    }

    if (octant[2] == 'R') {
        bounds.rightX = parentBounds.rightX;
        bounds.leftX = parentsCenter.get_coordinates()[1];
    }
    else if (octant[2] == 'L') {
        bounds.rightX = parentsCenter.get_coordinates()[1];
        bounds.leftX = parentBounds.leftX;
    }

    return bounds;
}

Octree::Octree(vector <Vertex> parentVertices, Bounds bounds, int level)
{
    for (int i = 0; i < 8; i++)
        Children[i] = nullptr;

    if (parentVertices.size() > 20) {
        for (auto vertex : parentVertices) {
            if (vertex.vertexInsideBounds(bounds))
                this->Vertices.push_back(vertex);
        }

        this->bounds = bounds;
        this->level = level + 1;
        this->center = findCenter(this->bounds);

        string octants[8] = {"TFR", "TFL", "TBL", "TBR", "BFR", "BFL", "BBL", "BBR"};

        for (int i = 0; i<8; i++)
            Children[i] = new Octree(this->Vertices, calculateBounds(octants[i], this->bounds, this->center), this->level);
    }
}
