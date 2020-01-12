#ifndef OCTREEMAINWINDOW_HPP
#define OCTREEMAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QFile>
#include <QScrollBar>

#include "guiQt3D.hpp"

using namespace std;

class MyLogWindow : public QPlainTextEdit
{
public:
    void appendMessage(const QString& text);
};

class OctreeMainWindow : public QMainWindow {
    public:
        OctreeMainWindow();
        
        QWidget* pTopWidget;
        MyLogWindow * pLogBox;
        QVBoxLayout *pHLayout;
        Qt3DWindow* pView;

        void keyPressEvent(QKeyEvent *event) override;
};

MyLogWindow& operator << (MyLogWindow& lw, string text);
MyLogWindow& operator << (MyLogWindow& lw, int number);

#endif