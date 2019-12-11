#ifndef FACES_HPP
#define FACES_HPP

#include <vector>
#include <array>
#include "vertex.hpp"

using namespace std;

class Faces
{
    private:
        array <int, 3> faceIndices;  // Niz sa 3 indexa vertexa;
    public:
        Faces(string fLine);         // Konstruktor koji čita red iz datoteke FORMAT: "f v1/x/x v2/x/x v3/x/x"
        array <int, 3> get_faceIndices();
};

#endif