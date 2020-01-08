#include "../include/faces.hpp"
#include "../include/objfile.hpp"
#include "../include/vertex.hpp"
#include "../include/guiQt3D.hpp"
#include "../include/octree.hpp"

#include <iostream>
#include <chrono>
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <Qt3DExtras>
#include <fstream>

using namespace std;

typedef array <Vertex *, 3> triangle;
void addTrisW(Qt3DWindow * pClass, vector <triangle> &triangleVector);
void startTree(Qt3DWindow * pView);

class MyMainWindow : public QMainWindow {
    public:
        MyMainWindow();

        QWidget* pTopWidget;
        QHBoxLayout *pHLayout;
        Qt3DWindow* pView;

        void keyPressEvent(QKeyEvent *event) override;

};

bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char *argv[])
{
    string filename1;
    string filename2;

    if (argc >= 3) {
        filename1 = argv[1];
        filename2 = argv[2];
    }
    else {
        cout << "Nema dovoljno argumenata." << endl;
        return 1;
    }

    if (!fileExists(filename1)) {
        cout << "Datoteka " << filename1 << "ne postoji." << endl;
        return 2;
    }

    if (!fileExists(filename2)) {
        cout << "Datoteka " << filename2 << "ne postoji." << endl;
        return 2;
    }

    QApplication app (argc, argv);
    MyMainWindow mainWindow;

    cout << "Učitavam prvi obj file :: ";
    auto t1 = chrono::high_resolution_clock::now();
    ObjFile file1 (filename1);
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    cout << duration << " ms" << endl;

    cout << "Učitavam drugi obj file :: ";
    t1 = chrono::high_resolution_clock::now();
    ObjFile file2 (filename2);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    cout << duration << " ms" << endl;

    cout << "Crtam prvi objekt :: ";
    t1 = chrono::high_resolution_clock::now();
    addTrisW(mainWindow.pView, file1.triangleVector);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    cout << duration << " ms" << endl;

    cout << "Crtam drugi objekt :: ";
    t1 = chrono::high_resolution_clock::now();
    addTrisW(mainWindow.pView, file2.triangleVector);
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    cout << duration << " ms" << endl;

    cout << "Stvaram prvo stablo :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree1(file1.triangleVector, findBounds(file1.get_vertexVector()), 0,  mainWindow.pView, file1.triangleVector.size());
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    cout << duration << " ms" << endl;

    cout << "Stvaram drugo stablo :: ";
    t1 = chrono::high_resolution_clock::now();
    Octree tree2(file2.triangleVector, findBounds(file2.get_vertexVector()), 0,  mainWindow.pView, file2.triangleVector.size());
    t2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
    cout << duration << " ms" << endl;
    
    mainWindow.resize(1024, 800);
    mainWindow.show();

    return app.exec();
}


void MyMainWindow::keyPressEvent(QKeyEvent *event) {
    switch( event->key() ){
        case Qt::Key_Right:
        break;
        case Qt::Key_Up:
        break;
        case Qt::Key_Down:
        break;
    }
}


MyMainWindow::MyMainWindow() {
// napravi 3D prozor i widget
    pView = new Qt3DWindow;
// napravi glavni layout aplikacije
    pHLayout = new QHBoxLayout;
// dodaj 3d widget u glavni layout aplikacije
    pHLayout->addWidget(pView->pMyWidget);
// napravi glavni widget aplikacije
    pTopWidget = new QWidget;
// postavi glavni layout za glavni widget aplikacije
    pTopWidget->setLayout(pHLayout);
// postavi glavni widget aplikacije kao centralni
    setCentralWidget(pTopWidget);
}

void addTrisW(Qt3DWindow * pClass, vector <triangle> &triangleVector)
{
    ulong step = 100;

    if (triangleVector.size() > step) {
        ulong offset = step;
        ulong index = 0;

        do {
            vector <triangle> tempVec;
            if (triangleVector.size() - offset > step) {
                for (ulong i = index; i < offset; i++) {
                    tempVec.push_back(triangleVector[i]);
                    index++;
                }
                offset += step;
            }
            else
            {
                for (ulong i = index; i< triangleVector.size(); i++) {
                    tempVec.push_back(triangleVector[i]);
                    index++;
                }
                offset += triangleVector.size() - offset;

            }
            pClass->AddTris(tempVec);
        } while (offset < triangleVector.size());
    }
    else
        pClass->AddTris(triangleVector);
}