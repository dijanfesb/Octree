#include "../include/octree.hpp"

#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <thread>
#include <future>

#define CHILDREN_NONE 0
#define CHILDREN_NODE_1 1
#define CHILDREN_NODE_2 2
#define CHILDREN_BOTH 3

using namespace std;

const char *Octree::octants[8] = {"TFR", "TFL", "TRL", "TRR", "BFR", "BFL", "BRL", "BRR"};

vector <Vertex> findVerticesInsideBounds(vector <Vertex> vertices, Bounds bounds)
{
    vector <Vertex> insideVertices;

    for (auto vertex : vertices) {
        if (vertex.insideBounds(bounds))
            insideVertices.push_back(vertex);
    }

    return insideVertices;
}

bool Vertex::compare_x(const Vertex& v1, const Vertex& v2)
{
    return Vertex(v1).getCoordinates()[0] < Vertex(v2).getCoordinates()[0];
}

bool Vertex::compare_y(const Vertex& v1, const Vertex& v2) 
{
    return Vertex(v1).getCoordinates()[1] < Vertex(v2).getCoordinates()[1];
}

bool Vertex::compare_z(const Vertex& v1, const Vertex& v2)
{
    return Vertex(v1).getCoordinates()[2] < Vertex(v2).getCoordinates()[2];
}

Octree::Octree(vector <pTriangle> &triangles_parent, vector <Vertex>& vertexVector)
{
    this->bounds = Bounds::find(vertexVector);
    this->level = 0;
    this->center = this->bounds.findCenter();
    this->triangles = triangles_parent;
    size_t totalTris = triangles_parent.size();

    array <Octree *, 8> children;
    array <thread * , 8> threads = {nullptr};

    for (int i = 0; i<8; i++) {
        Bounds childBounds = this->bounds.calculate(this->octants[i], this->center);
        vector <pTriangle> childTris = childBounds.findTrianglesInside(this->triangles);

        if (childTris.size() < 0.8*triangles.size() && childTris.size() > (0.25/100)*totalTris) {
            threads[i] = new thread(&Octree::insert, childTris, childBounds, totalTris, &children[i], this->level);
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

Octree::Octree(vector <pTriangle> &triangles_parent, Bounds bounds, size_t totalTris, int level)
{
    this->bounds = bounds;
    this->level = level + 1;
    this->center = this->bounds.findCenter();
    this->triangles = triangles_parent;

    for (int i = 0; i<8; i++) {
        Bounds childBounds = this->bounds.calculate(this->octants[i], this->center);
        vector <pTriangle> childTris = childBounds.findTrianglesInside(this->triangles);

        if (childTris.size() < 0.9*triangles.size() && childTris.size() > (0.025/100)*totalTris) {
            Children[i] = new Octree(childTris, this->bounds.calculate(this->octants[i], this->center), totalTris, this->level);
        }
        else
            Children[i] = nullptr;
    } 
}

Bounds Octree::getBounds()
{
    return this->bounds;
}

int Octree::getLevel()
{
    return this->level;
}

array <Octree *, 8> Octree::getChildren()
{
    return this->Children;
}

int Octree::insert(vector <pTriangle> triangles_parent, Bounds bounds, size_t totalTris, Octree ** pInsert, int level)
{
    Octree * pChild = new Octree(triangles_parent, bounds, totalTris, level);
    *pInsert = pChild;
    return (pChild ? 0 : 1);
}

int Octree::numberOfChildren()
{
    int c = 0;

    for (auto child : Children)
        if (child)
            c++;
            
    return c;
}

bool Octree::collides(Octree& o2)
{
    vector <Octree *> pairVector;
    pairVector.push_back(this);
    pairVector.push_back(&o2);

    while (pairVector.size()) {
        Octree* t1 = pairVector.back();
        pairVector.pop_back();
        Octree* t2 = pairVector.back();
        pairVector.pop_back();

        if (t1->bounds.intersect(t2->bounds)) {
            switch (t1->childrenRelation(*t2)) {
            case CHILDREN_NONE:
                for (auto triangle1 : t1->triangles)
                    for (auto triangle2 : t2->triangles) {
                        if (CGAL::intersection(Face::toTriangle3(triangle1), Face::toTriangle3(triangle2)))
                            return true;
                    }
                break;
            case CHILDREN_NODE_1:
                for (auto child1 : t1->Children)
                        if (child1) {
                            pairVector.push_back(child1);
                            pairVector.push_back(t2);
                        }
                break;
            case CHILDREN_NODE_2:
                for (auto child2 : t2->Children)
                        if (child2) {
                            pairVector.push_back(t1);
                            pairVector.push_back(child2);
                        }
                break;
            case CHILDREN_BOTH:
                for (auto child1 : t1->Children)
                    for (auto child2 : t2->Children)
                        if (child1 && child2) {
                            pairVector.push_back(child1);
                            pairVector.push_back(child2);
                        }
                break;
            }
        }
        else if (!pairVector.size()) {
            return false;
        }
    }

    return false;
}

int Octree::childrenRelation(Octree &o2)                  
{                                                             
    if (!(this->numberOfChildren() || o2.numberOfChildren()))  
        return CHILDREN_NONE;                              
    if (this->numberOfChildren() && o2.numberOfChildren())      
        return CHILDREN_BOTH;
    if (this->numberOfChildren())
        return CHILDREN_NODE_1;
    if (o2.numberOfChildren())
        return CHILDREN_NODE_2;

    return -1;
}