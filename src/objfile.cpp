#include "../include/objfile.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ObjFile::ObjFile(string filename)
{
    ifstream obj(filename, ios::in);

    Vertex emptyVertex(0, 0, 0);

    vertexVector.push_back(emptyVertex);

    while (!obj.eof()) {
        string line;
        
        getline(obj, line);

        if (line.find("v ") != std::string::npos) {
            Vertex temp(line);
            vertexVector.push_back(temp);
        }
        else if (line.find("f ") != std::string::npos) {
            Faces temp(line);
            facesVector.push_back(temp);
        }
        else if (line.find("o ") != std::string::npos) {
            char tmpStr[128];
            sscanf(line.c_str(), "o %s", tmpStr);
            name = tmpStr;
        }
    }

    for (unsigned long i = 0; i<facesVector.size(); i++) {
        array <Vertex *, 3> tempArray;
        array <int, 3> vertexIndex = facesVector[i].get_faceIndices();

        for (int j=0; j<3; j++) {
            tempArray[j] = &(vertexVector[vertexIndex[j]]); // Dodaj pointere u niz vertex pointera;
        }

        triangleVector.push_back(tempArray);
    }

    obj.close();
}


vector <Vertex> ObjFile::get_vertexVector()
{
    return this->vertexVector;
}

void ObjFile::move(double x, double y, double z)
{
    for (auto vertex : this->vertexVector) {
        auto coordinates = vertex.get_coordinates();
        double _x = coordinates[0];
        double _y = coordinates[1];
        double _z = coordinates[1];

        vertex.set_coordinates(x+_x, y+_y, z+_z);
    }
}
