#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <vector>
#include <array>
#include "vertex.hpp"
#include "bounds.hpp"
#include "faces.hpp"

class Octree {
private:
    vector <array <Vertex *, 3>> triangles;
    int level;
    Vertex center;
    Bounds bounds;
    static string octants[8];
    array <Octree *, 8> Children;
public:
    Octree(vector <array <Vertex *, 3>> &triangles_parent, Bounds bounds, size_t totalTris, int level = -1);
    Bounds get_bounds();
    int get_level();
    array <Octree *, 8> get_children();
};

vector <array <Vertex *, 3>> findTrisInsideBounds(vector <array <Vertex *, 3>> triangles, Bounds bounds);
Vertex findCenter(Bounds bounds);
Bounds findBounds(vector <Vertex> Vertices);
Bounds calculateBounds(string octant, Bounds parentBounds, Vertex parentsCenter);
bool compare_x(const Vertex& v1, const Vertex& v2);
bool compare_y(const Vertex& v1, const Vertex& v2);
bool compare_z(const Vertex& v1, const Vertex& v2);

#endif