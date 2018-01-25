#ifndef SECTORWALL_H
#define SECTORWALL_H

#include "Wall.h"

class Sector;

class SectorWall : public Wall
{
public:
	SectorWall();
	SectorWall(const Vector2f& p1, const Vector2f& p2);
	SectorWall(const Vector2f& p1, const Vector2f& p2, Sector* neighbour);

	const Sector* getNeighbour() const;

	void setNeighbour(Sector* sector);

private:
	Sector* neighbour;
};

#endif
