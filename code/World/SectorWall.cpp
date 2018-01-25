#include "SectorWall.h"
#include "Sector.h"

SectorWall::SectorWall() :
Wall(),
neighbour(nullptr)
{
}

SectorWall::SectorWall(const Vector2f& p1, const Vector2f& p2) :
Wall(p1, p2),
neighbour(nullptr)
{
}

SectorWall::SectorWall(const Vector2f& p1, const Vector2f& p2, Sector* neighbour) :
Wall(p1, p2),
neighbour(neighbour)
{
}

const Sector* SectorWall::getNeighbour() const
{
	return neighbour;
}

void SectorWall::setNeighbour(Sector* sector)
{
	neighbour = sector;
}
