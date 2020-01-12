#include <iostream>
#include <chrono>
#include <QApplication>
#include <QMainWindow>
#include <fstream>
#include <thread>

#include "../include/octree.hpp"
#include "../include/bounds.hpp"
#include "../include/vertex.hpp"
#include "../include/octreeMainWindow.hpp"
#include "../include/guiQt3D.hpp"
#include "../include/objfile.hpp"

using namespace std;

typedef array <Vertex *, 3> triangle;

bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    OctreeMainWindow mainWindow;
    Qt3DWindow *p3DWidget = mainWindow.pView;

    mainWindow.showMaximized();

    string filename1;
    string filename2;

    if (argc >= 3) {
        filename1 = argv[1];
        filename2 = argv[2];
    }
    else {
        *(mainWindow.pLogBox) << "Nema dovoljno argumenata." << "\n";
        return 1;
    }

    if (!fileExists(filename1)) {
        *(mainWindow.pLogBox) << "Datoteka " << filename1 << "ne postoji." << "\n";
        return 2;
    }

    if (!fileExists(filename2)) {
        *(mainWindow.pLogBox) << "Datoteka " << filename2 << "ne postoji." << "\n";
        return 2;
    }

    *(mainWindow.pLogBox) << "Učitavam prvi obj file :: ";
    auto t1 = chrono::high_resolution_clock::now();
    ObjFile file1 (filename1);
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Učitavam drugi obj file :: ";
    t1 = chrono::high_resolution_clock::now();
    ObjFile file2 (filename2);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtam prvi objekt :: ";
    t1 = chrono::high_resolution_clock::now();
    p3DWidget->addTrisW(file1.triangleVector, p3DWidget->pPhongRed);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtam drugi objekt :: ";
    t1 = chrono::high_resolution_clock::now();
    p3DWidget->addTrisW(file2.triangleVector, p3DWidget->pPhongRed);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Stvaram prvo stablo :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree1(file1.triangleVector, findBounds(file1.get_vertexVector()), file1.triangleVector.size());
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Stvaram drugo stablo :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree2(file2.triangleVector, findBounds(file2.get_vertexVector()), file2.triangleVector.size());
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";
    
    *(mainWindow.pLogBox) << "Crtam prvi octree :: ";
    t1 = chrono::high_resolution_clock::now();
    p3DWidget->DrawOctree(&tree1);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtam drugi octree :: ";
    t1 = chrono::high_resolution_clock::now();
    p3DWidget->DrawOctree(&tree2);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << (tree1.objectColision(tree2) ? "Sudar" : "Nema sudara") << "\n";

    p3DWidget->pObjFile1 = &file1;
    p3DWidget->pObjFile2 = &file2;

    p3DWidget->pTree1 = &tree1;
    p3DWidget->pTree2 = &tree2;

    return app.exec();
}