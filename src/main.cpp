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

typedef array <Vertex*, 3> triangle;

bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

template<class F, class... Args>
auto functionTimeMs(F &&function, Args&&... args){
    auto t1=chrono::high_resolution_clock::now();
    *function(std::forward<Args>(args)...);
    return (chrono::duration_cast <chrono::milliseconds>(chrono::high_resolution_clock::now()-t1).count());
}

template <class F, class T, class... Args>
auto functionTimeMs(F &&function, T* t, Args&&... args){
    auto t1=chrono::high_resolution_clock::now();
    (t->*function)(std::forward<Args>(args)...);
    return (chrono::duration_cast <chrono::milliseconds>(chrono::high_resolution_clock::now()-t1).count());
}

bool bruteForce(ObjFile& f1, ObjFile& f2)
{
    for (auto triangle1 : f1.triangleVector)
        for (auto triangle2 : f2.triangleVector) {
            auto result = intersection(toTriangle3(triangle1), toTriangle3(triangle2));
                if (result)
                    return true;
        }
    return false;
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

    *(mainWindow.pLogBox) << "Početak :: ";
    auto startTime = chrono::high_resolution_clock::now();

    *(mainWindow.pLogBox) << "Učitavam prvi obj file :: ";
    auto t1 = chrono::high_resolution_clock::now();
    ObjFile file1 (filename1);
    auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Učitavam drugi obj file :: ";
    t1 = chrono::high_resolution_clock::now();
    ObjFile file2 (filename2);
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtam prvi objekt :: "    
    << functionTimeMs(&Qt3DWindow::addTrisW, p3DWidget, file1.triangleVector, p3DWidget->pPhongRed);
    *(mainWindow.pLogBox) << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtam drugi objekt :: "    
    << functionTimeMs(&Qt3DWindow::addTrisW, p3DWidget, file2.triangleVector, p3DWidget->pPhongRed);
    *(mainWindow.pLogBox) << " ms" << "\n";

    *(mainWindow.pLogBox) << "Stvaram prvo stablo :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree1(file1.triangleVector, file1.vertexVector);
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Stvaram prvo stablo :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree2(file2.triangleVector, file2.vertexVector);
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";
    
    *(mainWindow.pLogBox) << "Crtam prvi octree :: "    
    << functionTimeMs(&Qt3DWindow::DrawOctree, p3DWidget, &tree1, 0, 3);
    *(mainWindow.pLogBox) << " ms" << "\n";

     *(mainWindow.pLogBox) << "Crtam drugi octree :: "    
    << functionTimeMs(&Qt3DWindow::DrawOctree, p3DWidget, &tree2, 0, 3);
    *(mainWindow.pLogBox) << " ms" << "\n";

    t1 = chrono::high_resolution_clock::now();
    *(mainWindow.pLogBox) << (tree1.octreeCollides(tree2) ? "Sudar" : "Nema sudara") << " :: ";
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    p3DWidget->pObjFile1 = &file1;
    p3DWidget->pObjFile2 = &file2;

    p3DWidget->pTree1 = &tree1;
    p3DWidget->pTree2 = &tree2;

    return app.exec();
}