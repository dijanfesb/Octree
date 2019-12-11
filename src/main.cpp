#include "../include/faces.hpp"
#include "../include/objfile.hpp"
#include "../include/vertex.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = argv[1];

    ObjFile file (filename);

    return 0;
}
