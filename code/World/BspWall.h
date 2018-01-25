#ifndef BSPWALL_H
#define BSPWALL_H

#include "Wall.h"

class SectorWall;

class BspWall : public Wall
{
public:
	BspWall();
	BspWall(const Vector2f& p1, const Vector2f& p2);
	BspWall(const Vector2f& p1, const Vector2f& p2, float nFloor, float nCeiling);

	BspWall& operator=(const SectorWall& rhs);

	bool isWindow() const;

	float getNeighbourFloor() const;
	float getNeighbourCeiling() const;

private:
	bool window;
	float neighbourFloor;
	float neighbourCeiling;
};

#endif
