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
            Face temp(line);
            facesVector.push_back(temp);
        }
        else if (line.find("o ") != std::string::npos) {
            char tmpStr[128];
            sscanf(line.c_str(), "o %s", tmpStr);
            name = tmpStr;
        }
    }

    for (unsigned long i = 0; i<facesVector.size(); i++) {
        pTriangle tempArray;
        array <int, 3> vertexIndex = facesVector[i].getFaceIndices();

        for (int j=0; j<3; j++) {
            tempArray[j] = &(vertexVector[vertexIndex[j]]); // Dodaj pointere u niz vertex pointera;
        }

        triangleVector.push_back(tempArray);
    }

    obj.close();
}

void ObjFile::move(double x, double y, double z)
{
    for (auto vertex : this->vertexVector) {
        auto coordinates = vertex.getCoordinates();
        double _x = coordinates[0];
        double _y = coordinates[1];
        double _z = coordinates[1];

        vertex.setCoordinates(x+_x, y+_y, z+_z);
    }
}
