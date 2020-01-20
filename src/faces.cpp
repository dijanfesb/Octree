#include "../include/faces.hpp"

#include <string>
#include <string.h>
#include <sstream>
#include <array>
#include <iostream>

using namespace std;

Faces::Faces(string fLine)
{
    /*
     * FORMAT: f v/x/x   v/x/x   v/x/x
     */

    char * cString = &fLine[0];

    int tempArr[3] = {0};

    if (sscanf(cString, "f %d%*s %d%*s %d%*s", &tempArr[0], &tempArr[1], &tempArr[2]) < 3)
        sscanf(cString, "f %d %d %d", &tempArr[0], &tempArr[1], &tempArr[2]);

    for (int i=0; i<3; i++)
        faceIndices[i] = tempArr[i];
}

Faces::Faces()
{
    for (int i=0; i<3; i++)
        faceIndices[i] = 0;
}

array <int, 3> Faces::get_faceIndices()
{
    return faceIndices;
}

void Faces::set_faceIndices_zero()
{
    for (int i=0; i<3; i++)
        faceIndices[i] = 0;
}

int Faces::operator[] (int index)
{
    return faceIndices[index];
}

array <Vertex, 3> Faces::get_vertices(vector <Vertex> vertexVec)
{
    array <Vertex, 3> ret;

    for (int i = 0; i<3; i++)
        ret[i] = vertexVec[this->faceIndices[i]];

    return ret;
}

bool triangleInsideBounds(array <Vertex *, 3> triangle, Bounds bounds)
{
    for (auto vertex : triangle)
        if (vertex->vertexInsideBounds(bounds))
            return true;

    return false;
}

Kernel::Triangle_3 toTriangle3(array <Vertex *, 3> triangle)
{
    return Kernel::Triangle_3(triangle[0]->toPoint3(), triangle[1]->toPoint3(), triangle[2]->toPoint3());
}

