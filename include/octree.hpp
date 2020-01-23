#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <vector>
#include <array>

#include "bounds.hpp"
#include "vertex.hpp"
#include "face.hpp"

#include <CGAL/intersections.h>

class Octree {
private:
    vector <pTriangle> triangles;
    int level;
    Vertex center;
    Bounds bounds;
    array <Octree *, 8> Children;
public:
    static const char *octants[8];
    Octree(vector <pTriangle> &triangles_parent, vector <Vertex>& vertexVector);
    Octree(vector <pTriangle> &triangles_parent, Bounds bounds, size_t totalTris, int level = -1);
    Bounds getBounds();
    int getLevel();
    array <Octree *, 8> getChildren();
    int numberOfChildren();
    bool collides(Octree& o2);
    int childrenRelation(Octree &o2);
    static int insert(vector <pTriangle> triangles_parent, Bounds bounds, size_t totalTris, Octree ** pInsert, int level); // Wrapper za std::thread
};

#endif