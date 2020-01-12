#include "../include/octreeMainWindow.hpp"

OctreeMainWindow::OctreeMainWindow() {
    pView = new Qt3DWindow;
    pHLayout = new QVBoxLayout;
    pLogBox = new MyLogWindow;

    QPalette LogBoxPalette = pLogBox->palette();
    LogBoxPalette.setColor(QPalette::Base, Qt::black);
    LogBoxPalette.setColor(QPalette::Text, Qt::green);
    pLogBox->setPalette(LogBoxPalette);
    pLogBox->setReadOnly(true);

    pHLayout->addWidget(pView->pMyWidget);
    pView->pMyWidget->setMinimumHeight(500);
    pHLayout->setStretch(0, 2);

    pHLayout->addWidget(pLogBox);
    
    pTopWidget = new QWidget;
    pTopWidget->setLayout(pHLayout);
    setCentralWidget(pTopWidget);
}


void MyLogWindow::appendMessage(const QString& text)
{
    this->moveCursor (QTextCursor::End);
    this->insertPlainText (text);
    this->moveCursor (QTextCursor::End);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
}

MyLogWindow& operator << (MyLogWindow& lw, string text)
{
    lw.appendMessage(QString::fromStdString(text));
    return lw;
}
 
MyLogWindow& operator << (MyLogWindow& lw, int number)
{
    lw.appendMessage(QString::fromStdString(to_string(number)));
    return lw;
}

void OctreeMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_0:
            pView->CreateRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1, 0, 0);
            pView->DrawOctree(pView->pTree2, 0, 0);
        break;
        case Qt::Key_1:
            pView->CreateRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1, 1, 1);
            pView->DrawOctree(pView->pTree2, 1, 1);
        break;
        case Qt::Key_2:
            pView->CreateRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1, 2, 2);
            pView->DrawOctree(pView->pTree2, 2, 2);
        break;
        case Qt::Key_3:
            pView->CreateRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1, 3, 3);
            pView->DrawOctree(pView->pTree2, 3, 3);
        break;
        case Qt::Key_4:
            pView->CreateRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1, 4, 4);
            pView->DrawOctree(pView->pTree2, 4, 4);
        break;
        case Qt::Key_5:
            pView->CreateRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1, 5, 5);
            pView->DrawOctree(pView->pTree2, 5, 5);
        break;
        case Qt::Key_T:
            pView->CreateRootEntity();
            pView->showTris = !pView->showTris;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1);
            pView->DrawOctree(pView->pTree2);
        break;
        case Qt::Key_O:
            pView->CreateRootEntity();
            pView->showTree = !pView->showTree;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->DrawOctree(pView->pTree1);
            pView->DrawOctree(pView->pTree2);
        break;
        case Qt::Key_W:
            pView->CreateRootEntity();
            pView->DrawWireframe(pView->pObjFile1->triangleVector);
            pView->DrawWireframe(pView->pObjFile2->triangleVector);
        break;

    }
}