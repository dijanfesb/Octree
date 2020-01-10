#ifndef OCTREEMAINWINDOW_HPP
#define OCTREEMAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include "guiQt3D.hpp"

class OctreeMainWindow : public QMainWindow {
    public:
        OctreeMainWindow();
        
        QWidget* pTopWidget;
        QVBoxLayout *pHLayout;
        Qt3DWindow* pView;
};

#endif