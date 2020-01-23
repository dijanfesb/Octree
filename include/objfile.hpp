#ifndef OBJFILE_HPP
#define OBJFILE_HPP

#include <vector>

#include "face.hpp"

class ObjFile
{
    public:
        string name;
        ObjFile(string filename);
        vector <Face> facesVector;            // Vector svih faceova
        vector <pTriangle> triangleVector;     // Vektor trokuta
        vector <Vertex> vertexVector;         // Vector svih vertexa
        void move(double x, double y, double z);
};

#endif