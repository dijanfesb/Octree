#include "../include/guiQt3D.hpp"

Qt3DWindow::Qt3DWindow(){
// podesi boju pozadine
    this->defaultFrameGraph()->setClearColor(QColor(255,255,255));
// Camera
    pCamera = this->camera();
    pCamera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    pCamera->setPosition(QVector3D(10.0f, 10.0f, 10.0f));
    pCamera->setUpVector(QVector3D(0, 1, 0));
    pCamera->setViewCenter(QVector3D(0, 0, 0));
// ukljuci trokute
    showTris = true;
// napravi korijen
    this->CreateRootEntity();
// prikazi 3D prozor
    this->show();
// napravi widget od ovog prozora
    this->pMyWidget = QWidget::createWindowContainer(this);
    this->setFlags(Qt::FramelessWindowHint);
}
void Qt3DWindow::CreateRootEntity(){
// Root entity
    pRootEntity = new Qt3DCore::QEntity();
// napravi kontrolu kamere
    Qt3DExtras::QOrbitCameraController* pCamController = new Qt3DExtras::QOrbitCameraController(pRootEntity);
    pCamController->setLinearSpeed( 200.0f );
    pCamController->setLookSpeed( 400.0f );
    pCamController->setCamera(pCamera);
// svitlo
    Qt3DCore::QEntity* pCamLightEntity = new Qt3DCore::QEntity(pRootEntity);
    Qt3DRender::QDirectionalLight* pCamLight = new Qt3DRender::QDirectionalLight();
    pCamLight->setWorldDirection(QVector3D(0.0f, -0.0f, -1.0f));
    pCamLight->setColor(QColor::fromRgbF(1.0, 1.0, 1.0, 1.0));
    pCamLightEntity->addComponent(pCamLight);
// Materiali
    pSpecularWhite = new Qt3DExtras::QPhongMaterial(pRootEntity);
    pSpecularWhite->setDiffuse(QColor(255, 255, 255));
    pSpecularWhite->setSpecular(QColor(255, 255, 255));
    pSpecularWhite->setAmbient(QColor(255, 255, 255));
    pPhongRed = new Qt3DExtras::QPhongMaterial(pRootEntity);
    pPhongRed->setDiffuse(QColor::fromRgbF(1.0, 0.0, 0.0, 1.0));
    pPhongGreen = new Qt3DExtras::QPhongMaterial(pRootEntity);
    pPhongGreen->setDiffuse(QColor::fromRgbF(0.0, 1.0, 0.0, 1.0));
    pPhongBlue = new Qt3DExtras::QPhongMaterial(pRootEntity);
    pPhongBlue->setDiffuse(QColor::fromRgbF(0.0, 0.0, 1.0, 1.0));
    pPhongWhite = new Qt3DExtras::QPhongMaterial(pRootEntity);
    pPhongWhite->setDiffuse(QColor::fromRgbF(1.0, 1.0, 1.0, 1.0));
// font
    pCourier = new QFont("Courier New", 32, 75, false);
// stvaranje geometrije
    if(this->showTris){
        // vector <array <QVector3D, 3>> triangleVector;
        // array <QVector3D, 3> face;
        // face[0] = QVector3D(1.0f, 0.0f, 0.0f);
        // face[1] = QVector3D(-1.0f, 0.0f, 0.0f);
        // face[2] = QVector3D(0.0f, -1.0f, 1.0f);
        // triangleVector.push_back(face);
        // face[0] = QVector3D(-1.0f, 0.0f, 0.0f);
        // face[1] = QVector3D(1.0f,  0.0f, 0.0f);
        // face[2] = QVector3D(0.0f, 1.0f, 0.0f);
		// triangleVector.push_back(face);
		// face[0] = QVector3D(-1.0f, 5.0f, 0.0f);
		// face[1] = QVector3D(1.0f, 5.0f, 0.0f);
		// face[2] = QVector3D(0.0f, 6.0f, 0.0f);
        // triangleVector.push_back(face);
        // this->AddTris(triangleVector);
    }
    // this->AddLines();
    // this->AddText("x", QVector3D(2, 0, 0), pPhongRed);
    // this->AddText("y", QVector3D(0, 2, 0), pPhongGreen);
    // this->AddText("z", QVector3D(0, 0, 2), pPhongBlue);
// postavi geometriju
    this->setRootEntity(pRootEntity);
}

void Qt3DWindow::AddTris(vector <array <Vertex *, 3>> &triangleVector_Ext) {
    vector <array <QVector3D, 3>> triangleVector;

    for(auto triangle : triangleVector_Ext) {
        array <QVector3D, 3> tempQVector;
        for (int j=0; j<3; j++) {
            tempQVector[j] = QVector3D(triangle[j]->get_coordinates()[0],
                                       triangle[j]->get_coordinates()[1],
                                       triangle[j]->get_coordinates()[2]);
        }
        triangleVector.push_back(tempQVector);
    }

// stvaram entitet, renderer i geometriju
    Qt3DCore::QEntity* pTrisEntity = new Qt3DCore::QEntity(pRootEntity);
    Qt3DRender::QGeometryRenderer* pTrisRenderer = new Qt3DRender::QGeometryRenderer;
    Qt3DRender::QGeometry* pTrisGeometry = new Qt3DRender::QGeometry(pTrisRenderer);
// qt3d vertex i index bufferi
    Qt3DRender::QBuffer* pTrisVertexDataBuffer = new Qt3DRender::QBuffer(pTrisGeometry);
    Qt3DRender::QBuffer* pTrisIndexDataBuffer = new Qt3DRender::QBuffer(pTrisGeometry);
// stvaram podatke za vertex buffer
	QVector3D tn;
	QVector<QVector3D> trisVertices;
	for(auto it : triangleVector){
	    tn = QVector3D::normal(it[0], it[1], it[2]);
	    trisVertices << it[0] << tn;
	    trisVertices << it[1] << tn;
	    trisVertices << it[2] << tn;    void AddLines();

	}
// punim vertex buffer
	QByteArray trisVertexBufferData;
// broj koordinata i normala (broj trokuta * 3 vrha * (3 koordinate + 3 normale))
	trisVertexBufferData.resize(int(triangleVector.size()) * 3 * (3 + 3) * sizeof(float));
	float *trisRawVertexArray1 = reinterpret_cast<float *>(trisVertexBufferData.data());
	int idx = 0;
	for (const QVector3D &v : trisVertices) {
		trisRawVertexArray1[idx++] = v.x();
		trisRawVertexArray1[idx++] = v.y();
		trisRawVertexArray1[idx++] = v.z();
	}
// stvaram index buffer 
	QByteArray trisIndexBufferData;
// broj trokuta * 3 vrha
	trisIndexBufferData.resize(int(triangleVector.size()) * 3 * sizeof(ushort));
	ushort *trisRawIndexArray = reinterpret_cast<ushort *>(trisIndexBufferData.data());
	for (ulong i = 0; i < triangleVector.size(); ++i) {
		trisRawIndexArray[i * 3 + 0] = i * 3 + 0;
		trisRawIndexArray[i * 3 + 1] = i * 3 + 1;
		trisRawIndexArray[i * 3 + 2] = i * 3 + 2;
	}

// postavi buffere
    pTrisVertexDataBuffer->setData(trisVertexBufferData);
    pTrisIndexDataBuffer->setData(trisIndexBufferData);

// Attributes za Qt3D
    Qt3DRender::QAttribute* pTrisPositionAttribute = new Qt3DRender::QAttribute();
    pTrisPositionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    pTrisPositionAttribute->setBuffer(pTrisVertexDataBuffer);
    pTrisPositionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    pTrisPositionAttribute->setVertexSize(3);
    pTrisPositionAttribute->setByteOffset(0);
    pTrisPositionAttribute->setByteStride(2 * 3 * sizeof(float));
    pTrisPositionAttribute->setCount(int(triangleVector.size()) *3);
    pTrisPositionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
// normale
    Qt3DRender::QAttribute* pTrisNormalAttribute = new Qt3DRender::QAttribute();
    pTrisNormalAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    pTrisNormalAttribute->setBuffer(pTrisVertexDataBuffer);
    pTrisNormalAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    pTrisNormalAttribute->setVertexSize(3);
    pTrisNormalAttribute->setByteOffset(3 * sizeof(float));
    pTrisNormalAttribute->setByteStride(2 * 3 * sizeof(float));
    pTrisNormalAttribute->setCount(int(triangleVector.size()) *3);
    pTrisNormalAttribute->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());
// indeksi lica
    Qt3DRender::QAttribute* pTrisIndexAttribute = new Qt3DRender::QAttribute();
    pTrisIndexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    pTrisIndexAttribute->setBuffer(pTrisIndexDataBuffer);
    pTrisIndexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedShort);
    pTrisIndexAttribute->setVertexSize(1);
    pTrisIndexAttribute->setByteOffset(0);
    pTrisIndexAttribute->setByteStride(0);
    pTrisIndexAttribute->setCount(int(triangleVector.size()) *3);
// dodaj atribute
    pTrisGeometry->addAttribute(pTrisPositionAttribute);
    pTrisGeometry->addAttribute(pTrisNormalAttribute);
    pTrisGeometry->addAttribute(pTrisIndexAttribute);
// podešavam qt3d mesh objekt
    pTrisRenderer->setInstanceCount(1);
    pTrisRenderer->setFirstVertex(0);
    pTrisRenderer->setFirstInstance(0);
    pTrisRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
    pTrisRenderer->setGeometry(pTrisGeometry);
// broj trokuta * 3 tocke
    pTrisRenderer->setVertexCount(int(triangleVector.size()) *3);
// dodaj renderer u entitet
    pTrisEntity->addComponent(pTrisRenderer);
// dodaj materijal u entitet
    pTrisEntity->addComponent(pPhongBlue);
}

void Qt3DWindow::AddLines(vector <QVector3D> lines) {
// stvaram entitet, renderer i geometriju
    Qt3DCore::QEntity *linesEntity = new Qt3DCore::QEntity(pRootEntity);
    Qt3DRender::QGeometryRenderer *linesRenderer = new Qt3DRender::QGeometryRenderer(pRootEntity);
    Qt3DRender::QGeometry *linesGeometry = new Qt3DRender::QGeometry(pRootEntity);
// qt3d vertex i index baferi
    Qt3DRender::QBuffer *linesVertexDataBuffer = new Qt3DRender::QBuffer(linesGeometry);
    Qt3DRender::QBuffer *linesIndexDataBuffer = new Qt3DRender::QBuffer(linesGeometry);
// vrhovi
    // QVector3D lv0(-200.0f, 0.0f, 0.0f);
    // QVector3D lv1(200.0f, 0.0f, 0.0f);
    // QVector3D lv2(0.0f, -200.0f, 0.0f);
    // QVector3D lv3(0.0f, 200.0f, 0.0f);
    // QVector3D lv4(0.0f, 0.0f, -200.0f);
    // QVector3D lv5(0.0f, 0.0f, 200.0f);
// vektor sa koordinatama
    QVector<QVector3D> linesVertices;

    for (auto vertex : lines)
        linesVertices << vertex;

// indeksi vrhova - šest vrhova po tri koordinate
    QByteArray linesVertexBufferData;
    linesVertexBufferData.resize(lines.size() * 3 * sizeof(float));
    float *linesRawVertexArray = reinterpret_cast<float*>(linesVertexBufferData.data());
    int idx = 0;
    for (const QVector3D &v : linesVertices) {
        linesRawVertexArray[idx++] = v.x();
        linesRawVertexArray[idx++] = v.y();
        linesRawVertexArray[idx++] = v.z();
    }
 // connectivity between vertices
    QByteArray linesIndexBufferData;
    linesIndexBufferData.resize(lines.size() * sizeof(unsigned int)); // start to end
    unsigned int *linesRawIndexArray = reinterpret_cast<unsigned int*>(linesIndexBufferData.data());
    for (ulong i = 0; i < lines.size(); i++) {
        *linesRawIndexArray++ = i;
    }
// postavljam buffere
    linesVertexDataBuffer->setData(linesVertexBufferData);
    linesIndexDataBuffer->setData(linesIndexBufferData);
// stvaram atribute koordinata
    Qt3DRender::QAttribute *linePositionAttribute = new Qt3DRender::QAttribute(linesGeometry);
    linePositionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    linePositionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    linePositionAttribute->setVertexSize(3);
    linePositionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    linePositionAttribute->setBuffer(linesVertexDataBuffer);
    linePositionAttribute->setByteStride(3 * sizeof(float));
    linePositionAttribute->setCount(lines.size());
// stvaram atribute indeksa linija
    Qt3DRender::QAttribute *linesIndexAttribute = new Qt3DRender::QAttribute(linesGeometry);
    linesIndexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    linesIndexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    linesIndexAttribute->setBuffer(linesIndexDataBuffer);
    linesIndexAttribute->setCount(lines.size());
// dodajem atribute u geometriju
    linesGeometry->addAttribute(linePositionAttribute); // We add the vertices in the linesGeometry
    linesGeometry->addAttribute(linesIndexAttribute); // We add the indices linking the points in the linesGeometry
// dodajem geometriju
    linesRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    linesRenderer->setGeometry(linesGeometry);
// dodajem objekt
    linesEntity->addComponent(linesRenderer);
    linesEntity->addComponent(pPhongRed);
}

void Qt3DWindow::AddText(const QString& str, const QVector3D& pos, Qt3DExtras::QPhongMaterial* pMat, float scale) {
// stvaram entitet
    Qt3DCore::QEntity *text = new Qt3DCore::QEntity(pRootEntity);
// stvaram tekst objekt
    Qt3DExtras::QExtrudedTextMesh *textMesh = new Qt3DExtras::QExtrudedTextMesh();
    textMesh->setDepth(0.0f);
    textMesh->setFont(*pCourier);
    textMesh->setText(str);
    text->addComponent(pMat);
    text->addComponent(textMesh);
// mičem tekst objekt
    Qt3DCore::QTransform *textTransform = new Qt3DCore::QTransform();
    textTransform->setTranslation(pos);
    textTransform->setScale(scale);
    text->addComponent(textTransform);
}

void Qt3DWindow::DrawLines(Bounds bounds) {
    vector <QVector3D> lines;
    array <QVector3D, 8> points;

    points[0] = QVector3D(bounds.leftX, bounds.bottomY, bounds.backZ);
    points[1] = QVector3D(bounds.leftX, bounds.bottomY, bounds.frontZ);
    points[2] = QVector3D(bounds.leftX, bounds.topY, bounds.backZ);
    points[3] = QVector3D(bounds.leftX, bounds.topY, bounds.frontZ);
    points[4] = QVector3D(bounds.rightX, bounds.bottomY, bounds.backZ);
    points[5] = QVector3D(bounds.rightX, bounds.bottomY, bounds.frontZ);
    points[6] = QVector3D(bounds.rightX, bounds.topY, bounds.backZ);
    points[7] = QVector3D(bounds.rightX, bounds.topY, bounds.frontZ);

    lines.push_back(points[0]);
    lines.push_back(points[1]);
    lines.push_back(points[2]);
    lines.push_back(points[3]);
    lines.push_back(points[0]);
    lines.push_back(points[2]);
    lines.push_back(points[1]);
    lines.push_back(points[3]);
    lines.push_back(points[4]);
    lines.push_back(points[5]);
    lines.push_back(points[6]);
    lines.push_back(points[7]);
    lines.push_back(points[4]);
    lines.push_back(points[6]);
    lines.push_back(points[5]);
    lines.push_back(points[7]);
    lines.push_back(points[0]);
    lines.push_back(points[4]);
    lines.push_back(points[2]);
    lines.push_back(points[6]);
    lines.push_back(points[1]);
    lines.push_back(points[5]);
    lines.push_back(points[3]);
    lines.push_back(points[7]);

    this->AddLines(lines);
}