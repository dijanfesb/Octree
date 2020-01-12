#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <vector>
#include <array>

#include "bounds.hpp"
#include "vertex.hpp"
#include "faces.hpp"
class Octree {
private:
    vector <array <Vertex *, 3>> triangles;
    int level;
    Vertex center;
    Bounds bounds;
    array <Octree *, 8> Children;
public:
    static const char *octants[8];
    Octree(vector <array <Vertex *, 3>> &triangles_parent, Bounds bounds, size_t totalTris, int level = -1);
    Bounds get_bounds();
    int get_level();
    array <Octree *, 8> get_children();
    bool objectColision(Octree& t2);
};

Octree * oTreeInsert(vector <array <Vertex *, 3>> triangles_parent, Bounds bounds, size_t totalTris, Octree ** returnVal, int level);
vector <array <Vertex *, 3>> findTrisInsideBounds(vector <array <Vertex *, 3>> triangles, Bounds bounds);
Vertex findCenter(Bounds bounds);
Bounds findBounds(vector <Vertex> Vertices);
Bounds calculateBounds(const char * octant, Bounds parentBounds, Vertex parentsCenter);
bool compare_x(const Vertex& v1, const Vertex& v2);
bool compare_y(const Vertex& v1, const Vertex& v2);
bool compare_z(const Vertex& v1, const Vertex& v2);

#endif