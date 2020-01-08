#ifndef OBJFILE_HPP
#define OBJFILE_HPP

#include "vertex.hpp"
#include "faces.hpp"
#include <vector>

class ObjFile
{
    private:
        string name;
        vector <Vertex> vertexVector;                    // Vector svih vertexa
        vector <Faces> facesVector;                      // Vector svih faceova
    public:       
        ObjFile(string filename);
        vector <Vertex> get_vertexVector();
        vector <array <Vertex *, 3>> triangleVector;     // Vektor trokuta
};

#endif