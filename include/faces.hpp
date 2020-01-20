#ifndef FACES_HPP
#define FACES_HPP

#include <vector>
#include <array>

#include "vertex.hpp"
#include "bounds.hpp"

#include <CGAL/Point_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

class Faces
{
    private:
        array <int, 3> faceIndices;  // Niz sa 3 indexa vertexa;
    public:
        Faces();
        Faces(string fLine);         // Konstruktor koji čita red iz datoteke FORMAT: "f v1/x/x v2/x/x v3/x/x"
        array <int, 3> get_faceIndices();
        array <Vertex, 3> get_vertices(vector <Vertex> vertexVec);
        void set_faceIndices_zero();
        int operator[] (int index);
};

bool triangleInsideBounds(array <Vertex *, 3> triangle, Bounds bounds);
Kernel::Triangle_3 toTriangle3(array <Vertex *, 3> triangle);

#endif