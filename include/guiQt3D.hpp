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

using namespace std;

class Qt3DWindow : public Qt3DExtras::Qt3DWindow {
public:
    Qt3DWindow();

    void AddTris(vector <array <Vertex *, 3>> &triangleVector_Ext); // Do 30000 trokuta
    void addTrisW(vector <array <Vertex *, 3>> &triangleVector);
    void DrawOctree(Octree * root, int minLevel = -1, int maxLevel = -1); // min i max = -1 -> nema granica
    void AddLines(vector <QVector3D> lines);
    void DrawLines(Bounds bounds);
    void AddText(const QString& str, const QVector3D& pos, Qt3DExtras::QPhongMaterial* pMat, float scale);
    void CreateRootEntity();

    QWidget* pMyWidget;
    Qt3DCore::QEntity* pRootEntity;
    Qt3DRender::QCamera* pCamera;
    Qt3DExtras::QPhongMaterial* pSpecularWhite;
    Qt3DExtras::QPhongMaterial* pPhongRed;
    Qt3DExtras::QPhongMaterial* pPhongGreen;
    Qt3DExtras::QPhongMaterial* pPhongBlue;
    Qt3DExtras::QPhongMaterial* pPhongWhite;
    QFont* pCourier;

    bool showTris;
};
#endif // Qt3DWindow_H
