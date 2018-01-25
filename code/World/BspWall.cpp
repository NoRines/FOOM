#include "BspWall.h"
#include "SectorWall.h"
#include "Sector.h"

BspWall::BspWall() :
Wall(),
window(false),
neighbourFloor(0.0f),
neighbourCeiling(0.0f)
{
}

BspWall::BspWall(const Vector2f& p1, const Vector2f& p2) :
Wall(p1, p2),
window(false),
neighbourFloor(0.0f),
neighbourCeiling(0.0f)
{
}

BspWall::BspWall(const Vector2f& p1, const Vector2f& p2, float nFloor, float nCeiling) :
Wall(p1, p2),
window(true),
neighbourFloor(nFloor),
neighbourCeiling(nCeiling)
{
}

BspWall& BspWall::operator=(const SectorWall& rhs)
{
	setTopTexCoords(rhs.getTopTexCoords());
	setTopTexture(rhs.getTopTextureName());

	setMidTexCoords(rhs.getMidTexCoords());
	setMidTexture(rhs.getMidTextureName());

	setBottomTexCoords(rhs.getBottomTexCoords());
	setBottomTexture(rhs.getBottomTextureName());


	setPoint1(rhs.getPoint1());
	setPoint2(rhs.getPoint2());
	calculateNormal();

	if(rhs.getNeighbour() != nullptr)
	{
		window = true;
		neighbourFloor = rhs.getNeighbour()->getFloorHeight();
		neighbourCeiling = rhs.getNeighbour()->getCeilingHeight();
	}
}

bool BspWall::isWindow() const
{
	return window;
}

float BspWall::getNeighbourFloor() const
{
	return neighbourFloor;
}

float BspWall::getNeighbourCeiling() const
{
	return neighbourCeiling;
}
