#include "../include/faces.hpp"
#include "../include/objfile.hpp"
#include "../include/vertex.hpp"
#include "../include/guiQt3D.hpp"
#include "../include/octree.hpp"

#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <Qt3DExtras>

using namespace std;

class MyMainWindow : public QMainWindow {
    public:
        MyMainWindow();

        QWidget* pTopWidget;
        QHBoxLayout *pHLayout;
        Qt3DWindow* pView;

        void keyPressEvent(QKeyEvent *event) override;

};

int main(int argc, char *argv[])
{
    if (argc < 2)
        return -2;

    string filename = argv[1];

    ObjFile file (filename);

    Octree tree(file.get_vertexVector());

    QApplication app (argc, argv);
    MyMainWindow mainWindow;

    (mainWindow.pView)->AddTris(file.triangleVector);
    
    mainWindow.resize(800,600);
    mainWindow.show();

    return app.exec();
}


void MyMainWindow::keyPressEvent(QKeyEvent *event) {
    switch( event->key() ){
        case Qt::Key_T:
            pView->showTris = !pView->showTris;
            pView->CreateRootEntity();
        break;
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
// dodaj 3d widgget u glavni layout aplikacije
    pHLayout->addWidget(pView->pMyWidget);
// napravi glavni widget aplikacije
    pTopWidget = new QWidget;
// postavi glavni layout za glavni widget aplikacije
    pTopWidget->setLayout(pHLayout);
// postavi glavni widget aplikacije kao centralni
    setCentralWidget(pTopWidget);
}