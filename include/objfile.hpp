#ifndef OBJFILE_HPP
#define OBJFILE_HPP

#include <vector>

#include "faces.hpp"

class ObjFile
{
    private:
        string name;
        vector <Faces> facesVector;                      // Vector svih faceova
    public:       
        ObjFile(string filename);
        vector <Vertex> get_vertexVector();
        vector <array <Vertex *, 3>> triangleVector;     // Vektor trokuta
        vector <Vertex> vertexVector;                    // Vector svih vertexa
        vector <array <Vertex *, 3>> buildTriangleVector();
        void move(double x, double y, double z);
};

#endif