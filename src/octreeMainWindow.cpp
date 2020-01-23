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

MyLogWindow& MyLogWindow::operator << (string text)
{
    this->appendMessage(QString::fromStdString(text));
    return *this;
}
 
MyLogWindow& MyLogWindow::operator << (int number)
{
    this->appendMessage(QString::fromStdString(to_string(number)));
    return *this;
}

void OctreeMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_0:
            pView->createRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1, 0, 0);
            pView->drawOctree(pView->pTree2, 0, 0);
        break;
        case Qt::Key_1:
            pView->createRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1, 1, 1);
            pView->drawOctree(pView->pTree2, 1, 1);
        break;
        case Qt::Key_2:
            pView->createRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1, 2, 2);
            pView->drawOctree(pView->pTree2, 2, 2);
        break;
        case Qt::Key_3:
            pView->createRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1, 3, 3);
            pView->drawOctree(pView->pTree2, 3, 3);
        break;
        case Qt::Key_4:
            pView->createRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1, 4, 4);
            pView->drawOctree(pView->pTree2, 4, 4);
        break;
        case Qt::Key_5:
            pView->createRootEntity();
            pView->showTree = true;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1, 5, 5);
            pView->drawOctree(pView->pTree2, 5, 5);
        break;
        case Qt::Key_T:
            pView->createRootEntity();
            pView->showTris = !pView->showTris;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1);
            pView->drawOctree(pView->pTree2);
        break;
        case Qt::Key_O:
            pView->createRootEntity();
            pView->showTree = !pView->showTree;
            pView->addTrisW(pView->pObjFile1->triangleVector, pView->pPhongRed);
            pView->addTrisW(pView->pObjFile2->triangleVector, pView->pPhongRed);
            pView->drawOctree(pView->pTree1);
            pView->drawOctree(pView->pTree2);
        break;
        case Qt::Key_W:
            pView->createRootEntity();
            pView->drawWireframe(pView->pObjFile1->triangleVector);
            pView->drawWireframe(pView->pObjFile2->triangleVector);
        break;

    }
}