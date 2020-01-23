#include "../include/face.hpp"

#include <string>
#include <string.h>
#include <sstream>
#include <array>
#include <iostream>

using namespace std;

Face::Face(string fLine)
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

Face::Face()
{
    for (int i=0; i<3; i++)
        faceIndices[i] = 0;
}

array <int, 3> Face::getFaceIndices()
{
    return faceIndices;
}

int Face::operator[] (int index)
{
    return faceIndices[index];
}

array <Vertex, 3> Face::getVertices(vector <Vertex> vertexVec)
{
    array <Vertex, 3> ret;

    for (int i = 0; i<3; i++)
        ret[i] = vertexVec[this->faceIndices[i]];

    return ret;
}

Kernel::Triangle_3 Face::toTriangle3(pTriangle triangle)
{
    return Kernel::Triangle_3(triangle[0]->toPoint3(), triangle[1]->toPoint3(), triangle[2]->toPoint3());
}

