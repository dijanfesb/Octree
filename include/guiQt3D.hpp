#ifndef Qt3DWindow_H
#define Qt3DWindow_H

#include <QWidget>
#include <Qt3DExtras>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QDiffuseSpecularMaterial>

#include <array>
#include <vector>

#include "bounds.hpp"
#include "vertex.hpp"
#include "octree.hpp"
#include "objfile.hpp"

using namespace std;

class Qt3DWindow : public Qt3DExtras::Qt3DWindow {
public:
    Qt3DWindow();

    void addTris(vector <pTriangle> &triangleVector_Ext, Qt3DExtras::QPhongMaterial * material); // Do 30000 trokuta
    void addTrisW(vector <pTriangle> &triangleVector_Ext, Qt3DExtras::QPhongMaterial * material);
    void addLines(vector <QVector3D> lines, Qt3DExtras::QPhongMaterial* material);
    void addText(const QString& str, const QVector3D& pos, Qt3DExtras::QPhongMaterial* pMat, float scale);
    void drawOctree(Octree * root, int minLevel = -1, int maxLevel = -1); // min i max = -1 -> nema granica
    void drawLines(Bounds bounds, Qt3DExtras::QPhongMaterial * material);
    void drawWireframe(vector <pTriangle> &triangleVector_Ext);
    void createRootEntity();

    QWidget* pMyWidget;
    Qt3DCore::QEntity* pRootEntity;
    Qt3DRender::QCamera* pCamera;
    Qt3DExtras::QPhongMaterial* pSpecularWhite;
    Qt3DExtras::QPhongMaterial* pSpecularYellow;
    Qt3DExtras::QPhongMaterial* pSpecularGreen;
    Qt3DExtras::QPhongMaterial* pSpecularBlue;    
    Qt3DExtras::QPhongMaterial* pSpecularRed;
    Qt3DExtras::QPhongMaterial* pPhongRed;
    Qt3DExtras::QPhongMaterial* pPhongGreen;
    Qt3DExtras::QPhongMaterial* pPhongBlue;
    Qt3DExtras::QPhongMaterial* pPhongWhite;

    ObjFile* pObjFile1;
    ObjFile* pObjFile2;

    Octree* pTree1;
    Octree* pTree2;

    QFont* pCourier;

    bool showTris;
    bool showTree;
};
#endif // Qt3DWindow_H
