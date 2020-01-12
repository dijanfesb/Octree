#include "../include/octree.hpp"

#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <thread>
#include <future>

using namespace std;

const char *Octree::octants[8] = {"TFR", "TFL", "TBL", "TBR", "BFR", "BFL", "BBL", "BBR"};

Bounds findBounds(vector <Vertex> Vertices)
{
    Bounds bounds;

    bounds.leftX = (*min_element(Vertices.begin()+1, Vertices.end(), compare_x)).get_coordinates()[0];
    bounds.rightX = (*max_element(Vertices.begin()+1, Vertices.end(), compare_x)).get_coordinates()[0];
    bounds.bottomY = (*min_element(Vertices.begin()+1, Vertices.end(), compare_y)).get_coordinates()[1];
    bounds.topY = (*max_element(Vertices.begin()+1, Vertices.end(), compare_y)).get_coordinates()[1];
    bounds.backZ = (*min_element(Vertices.begin()+1, Vertices.end(), compare_z)).get_coordinates()[2];
    bounds.frontZ = (*max_element(Vertices.begin()+1, Vertices.end(), compare_z)).get_coordinates()[2];

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

Bounds calculateBounds(const char * octant, Bounds parentBounds, Vertex parentsCenter)
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

Octree::Octree(vector <array <Vertex *, 3>> &triangles_parent, vector <Vertex>& vertexVector)
{
    this->bounds = findBounds(vertexVector);
    this->level = 0;
    this->center = findCenter(this->bounds);
    this->triangles = triangles_parent;
    size_t totalTris = triangles_parent.size();

    array <Octree *, 8> children;
    array <thread * , 8> threads = {nullptr};

    for (int i = 0; i < 8; i++) {
        vector <array <Vertex*, 3>> childTris;
        Bounds childBounds = calculateBounds(this->octants[i], this->bounds, this->center);

        for (auto triangle : this->triangles)
            if (triangleInsideBounds(triangle, childBounds))
                childTris.push_back(triangle);

        if (childTris.size() < 0.8*triangles.size() && childTris.size() > (0.25/100)*totalTris) {
            threads[i] = new thread(oTreeInsert, childTris, childBounds, totalTris, &children[i], this->level);
        }
        else
            children[i] = nullptr;
    }

    for (auto thr : threads) {
        if (thr)
            thr->join();
    }

    for (int i = 0; i<8; i++) {
        Children[i] = children[i];
    }

}

Octree::Octree(vector <array <Vertex *, 3>> &triangles_parent, Bounds bounds, size_t totalTris, int level)
{
    this->bounds = bounds;
    this->level = level + 1;
    this->center = findCenter(this->bounds);
    this->triangles = triangles_parent;

    for (int i = 0; i<8; i++) {
        vector <array <Vertex *, 3>> childTris;
        Bounds childBounds = calculateBounds(this->octants[i], this->bounds, this->center);

        for (auto triangle : this->triangles)
            if (triangleInsideBounds(triangle, childBounds))
                childTris.push_back(triangle);

        if (childTris.size() < 0.9*triangles.size() && childTris.size() > (0.025/100)*totalTris) {
            Children[i] = new Octree(childTris, calculateBounds(this->octants[i], this->bounds, this->center), totalTris, this->level);
        }
        else
            Children[i] = nullptr;
    } 
}

Bounds Octree::get_bounds()
{
    return this->bounds;
}

int Octree::get_level()
{
    return this->level;
}

array <Octree *, 8> Octree::get_children()
{
    return this->Children;
}

bool Octree::objectColision(Octree& t2)
{
    Octree * o1 = this;
    Octree * o2 = &t2;

    if (!o1->bounds.BoundsCollision(o2->bounds))
        return false;

    return true;
}

Octree * oTreeInsert(vector <array <Vertex *, 3>> triangles_parent, Bounds bounds, size_t totalTris, Octree ** returnVal, int level)
{
    Octree * pChild = new Octree(triangles_parent, bounds, totalTris, level);
    *returnVal = pChild;
    return 0;
}