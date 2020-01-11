#include "../include/bounds.hpp"

using namespace std;

Bounds::Bounds()
{
	topY = bottomY = leftX = rightX = frontZ = backZ = 0;
}

array <Vertex, 8> Bounds::getCorners()
{
	array <Vertex, 8> corners;

	corners[0] = Vertex(this->leftX, this->bottomY, this->backZ);
    corners[1] = Vertex(this->leftX, this->bottomY, this->frontZ);
    corners[2] = Vertex(this->leftX, this->topY, this->backZ);
    corners[3] = Vertex(this->leftX, this->topY, this->frontZ);
    corners[4] = Vertex(this->rightX, this->bottomY, this->backZ);
    corners[5] = Vertex(this->rightX, this->bottomY, this->frontZ);
    corners[6] = Vertex(this->rightX, this->topY, this->backZ);
    corners[7] = Vertex(this->rightX, this->topY, this->frontZ);

	return corners;
}

bool Bounds::BoundsCollision(Bounds& b2)
{
    array <Vertex, 8> points1 = this->getCorners();
    array <Vertex, 8> points2 = b2.getCorners();

    for (auto vertex : points1)
        if (vertex.vertexInsideBounds(b2))
            return true;

    for (auto vertex : points2)
        if (vertex.vertexInsideBounds(*this))
            return true;

    return false;
}
