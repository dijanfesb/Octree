#include "../include/octree.hpp"
#include "../include/vertex.hpp"
#include "../include/bounds.hpp"
#include "../include/guiQt3D.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <QVector3D>


using namespace std;

string Octree::octants[8] = {"TFR", "TFL", "TBL", "TBR", "BFR", "BFL", "BBL", "BBR"};

Bounds findBounds(vector <Vertex> Vertices)
{
    Bounds bounds;

    bounds.topY = (*max_element(Vertices.begin()+1, Vertices.end(), compare_y)).get_coordinates()[1];
    bounds.bottomY = (*min_element(Vertices.begin()+1, Vertices.end(), compare_y)).get_coordinates()[1];
    bounds.leftX = (*min_element(Vertices.begin()+1, Vertices.end(), compare_x)).get_coordinates()[0];
    bounds.rightX = (*max_element(Vertices.begin()+1, Vertices.end(), compare_x)).get_coordinates()[0];
    bounds.frontZ = (*max_element(Vertices.begin()+1, Vertices.end(), compare_z)).get_coordinates()[2];
    bounds.backZ = (*min_element(Vertices.begin()+1, Vertices.end(), compare_z)).get_coordinates()[2];

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

Bounds calculateBounds(string octant, Bounds parentBounds, Vertex parentsCenter)
{
    // string Octant : [T/B][F/B][R/L]

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
        bounds.leftX = parentsCenter.get_coordinates()[0];
    }
    else if (octant[2] == 'L') {
        bounds.rightX = parentsCenter.get_coordinates()[0];
        bounds.leftX = parentBounds.leftX;
    }

    return bounds;
}

Octree::Octree(vector <array <Vertex *, 3>> &triangles, Bounds bounds, int level,  Qt3DWindow * win, size_t totalTris)
{
    this->bounds = bounds;
    this->level = level + 1;
    this->center = findCenter(this->bounds);
    this->triangles = triangles;

    win->DrawLines(this->bounds);
    win->AddText(QString::fromStdString(to_string(level)), 
                 QVector3D(this->center.get_coordinates()[0], 
                           this->center.get_coordinates()[1], 
                           this->center.get_coordinates()[2]),
                 win->pPhongRed, 2.0f*(1.0f/this->level));
    
    for (int i = 0; i<8; i++) {
        vector <array <Vertex *, 3>> childTris;
        Bounds childBounds = calculateBounds(this->octants[i], this->bounds, this->center);

        for (auto triangle : this->triangles)
            if (triangleInsideBounds(triangle, childBounds))
                childTris.push_back(triangle);

        if (childTris.size() < 0.8*triangles.size() && childTris.size() > 0.0015*totalTris) {
            Children[i] = new Octree(childTris, calculateBounds(this->octants[i], this->bounds, this->center), this->level, win, totalTris);
        }
        else
            Children[i] = nullptr;
    } 
}
