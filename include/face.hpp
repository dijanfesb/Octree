#ifndef FACE_HPP
#define FACE_HPP

#include <vector>
#include <array>

#include "vertex.hpp"
#include "bounds.hpp"

#include <CGAL/Point_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef array <Vertex *, 3> pTriangle;

class Face
{
    private:
        array <int, 3> faceIndices;  // Niz sa 3 indexa vertexa;
    public:
        Face();
        Face(string fLine);         // Konstruktor koji čita red iz datoteke FORMAT: "f v1/x/x v2/x/x v3/x/x"
        array <int, 3> getFaceIndices();
        array <Vertex, 3> getVertices(vector <Vertex> vertexVec);
        int operator[] (int index);
        static Kernel::Triangle_3 toTriangle3(pTriangle triangle);

};
#endif