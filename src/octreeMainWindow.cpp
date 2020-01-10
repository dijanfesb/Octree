#include "../include/octreeMainWindow.hpp"

OctreeMainWindow::OctreeMainWindow() {
    pView = new Qt3DWindow;
    pHLayout = new QVBoxLayout;
    pHLayout->addWidget(pView->pMyWidget);
    pTopWidget = new QWidget;
    pTopWidget->setLayout(pHLayout);
    setCentralWidget(pTopWidget);
}