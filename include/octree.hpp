#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <vector>
#include <array>
#include "vertex.hpp"
#include "bounds.hpp"

class Octree {
private:
    vector <Vertex> Vertices;
    int level;
    Vertex center;
    Bounds bounds;
    array <Octree *, 8> Children;
public:
    Octree(vector <Vertex> Vertices);
    Octree(vector <Vertex> parentVertices, Bounds bounds, int level);
};

vector <Vertex> findVerticesInsideBounds(vector <Vertex> vertices, Bounds bounds);
Vertex findCenter(Bounds bounds);
Bounds findBounds(vector <Vertex> Vertices);
Bounds calculateBounds(string octant, Bounds parentBounds, Vertex parentsCenter);
bool compare_x(const Vertex& v1, const Vertex& v2);
bool compare_y(const Vertex& v1, const Vertex& v2);
bool compare_z(const Vertex& v1, const Vertex& v2);

#endif