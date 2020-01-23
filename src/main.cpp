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

bool fileExists (const std::string& name);

template<class F, class... Args>
auto functionTimeMs(F &&function, Args&&... args) {
    auto t1=chrono::high_resolution_clock::now();
    *function(std::forward<Args>(args)...);
    return (chrono::duration_cast <chrono::milliseconds>(chrono::high_resolution_clock::now()-t1).count());
}

template <class F, class T, class... Args>
auto functionTimeMs(F &&function, T* t, Args&&... args) {
    auto t1=chrono::high_resolution_clock::now();
    (t->*function)(std::forward<Args>(args)...);
    return (chrono::duration_cast <chrono::milliseconds>(chrono::high_resolution_clock::now()-t1).count());
}

bool bruteForce(ObjFile& f1, ObjFile& f2);

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    OctreeMainWindow mainWindow;
    Qt3DWindow *p3DWidget = mainWindow.pView;

    mainWindow.showMaximized();

    string filename1;
    string filename2;
    bool bruteforce = false;

    if (argc < 3) {
        *(mainWindow.pLogBox) << "Nema dovoljno argumenata." << "\n";
        return 1;
    }
    else {
        filename1 = argv[1];
        filename2 = argv[2];
        if (argc == 4 && string(argv[3]) == string("--bruteforce"))
            bruteforce = true;
    }

    if (!fileExists(filename1)) {
        *(mainWindow.pLogBox) << "Datoteka " << filename1 << "ne postoji." << "\n";
        return 2;
    }

    if (!fileExists(filename2)) {
        *(mainWindow.pLogBox) << "Datoteka " << filename2 << "ne postoji." << "\n";
        return 2;
    }

    *(mainWindow.pLogBox) << "Učitavanje prve .obj datoteke :: ";
    auto t1 = chrono::high_resolution_clock::now();
    ObjFile file1 (filename1);
    auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Učitavanje druge .obj datoteke :: ";
    t1 = chrono::high_resolution_clock::now();
    ObjFile file2 (filename2);
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Stvaranje prve octree strukture :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree1(file1.triangleVector, file1.vertexVector);
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";
    
    *(mainWindow.pLogBox) << "Stvaranje druge octree strukture :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree2(file2.triangleVector, file2.vertexVector);
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtanje prvog objekta :: "    
    << functionTimeMs(&Qt3DWindow::addTrisW, p3DWidget, file1.triangleVector, p3DWidget->pPhongRed);
    *(mainWindow.pLogBox) << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtanje drugog objekta :: "    
    << functionTimeMs(&Qt3DWindow::addTrisW, p3DWidget, file2.triangleVector, p3DWidget->pPhongRed);
    *(mainWindow.pLogBox) << " ms" << "\n";
    
    *(mainWindow.pLogBox) << "Crtanje octree podjele za prvi objekt :: "
    << functionTimeMs(&Qt3DWindow::drawOctree, p3DWidget, &tree1, 0, 3);
    *(mainWindow.pLogBox) << " ms" << "\n";

    *(mainWindow.pLogBox) << "Crtanje octree podjele za drugi objekt :: "
    << functionTimeMs(&Qt3DWindow::drawOctree, p3DWidget, &tree2, 0, 3);
    *(mainWindow.pLogBox) << " ms" << "\n";

    t1 = chrono::high_resolution_clock::now();
    if (bruteforce)
        *(mainWindow.pLogBox) << (bruteForce(file1, file2) ? "Objekti se sudaraju" : "Objekti se ne sudaraju") << " :: ";
    else
        *(mainWindow.pLogBox) << (tree1.collides(tree2) ? "Objekti se sudaraju" : "Objekti se ne sudaraju") << " :: ";
    duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count();
    *(mainWindow.pLogBox) << duration << " ms" << "\n";

    p3DWidget->pObjFile1 = &file1;
    p3DWidget->pObjFile2 = &file2;

    p3DWidget->pTree1 = &tree1;
    p3DWidget->pTree2 = &tree2;

    return app.exec();
}

bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

bool bruteForce(ObjFile& f1, ObjFile& f2)
{
    for (auto triangle1 : f1.triangleVector)
        for (auto triangle2 : f2.triangleVector) {
            auto result = CGAL::intersection(Face::toTriangle3(triangle1), Face::toTriangle3(triangle2));
                if (result)
                    return true;
        }
    return false;
}