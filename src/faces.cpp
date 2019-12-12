#include "../include/faces.hpp"
#include <string>
#include <string.h>
#include <sstream>
#include <array>

using namespace std;

Faces::Faces(string fLine)
{
    /*
     * FORMAT: f v/x/x   v/x/x   v/x/x
     */

    char * cString = &fLine[0];

    int tempArr[3] = {0};

    sscanf(cString, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &tempArr[0], &tempArr[1], &tempArr[2]);

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