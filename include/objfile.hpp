#ifndef OBJFILE_HPP
#define OBJFILE_HPP

#include "vertex.hpp"
#include "faces.hpp"
#include <vector>

class ObjFile
{
    private:
        vector <Vertex> vertexVector;                    // Vector svih vertexa
        vector <Faces> facesVector;                      // Vector svih faceova
        vector <array <Vertex *, 3>> triangleVector;     // Vektor trokuta
    public:
        ObjFile(string filename);
};

#endif