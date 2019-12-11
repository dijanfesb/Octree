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

    int dumint = 0;
    char dumchar = 0;

    sscanf(cString, "%c %d/%d/%d %d/%d/%d %d/%d/%d", &dumchar,\
                &tempArr[0], &dumint, &dumint,\
                &tempArr[1], &dumint, &dumint,\
                &tempArr[2], &dumint, &dumint);

    for (int i=0; i<3; i++)
        faceIndices[i] = tempArr[i];
}

array <int, 3> Faces::get_faceIndices()
{
    return faceIndices;
}
