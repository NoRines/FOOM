#include "Sector.h"

Sector::Sector() :
floorTexName("default"),
ceilingTexName("default"),
floorHeight(-1.0f),
ceilingHeight(1.0f)
{
}

Sector::Sector(float floorHeight, float ceilingHeight) :
floorTexName("default"),
ceilingTexName("default"),
floorHeight(floorHeight),
ceilingHeight(ceilingHeight)
{
}

void Sector::addWall(const SectorWall& wall)
{
	walls.push_back(wall);
}

float Sector::getFloorHeight() const
{
	return floorHeight;
}

float Sector::getCeilingHeight() const
{
	return ceilingHeight;
}

void Sector::setFloorHeight(float height)
{
	floorHeight = height;
}

void Sector::setCeilingHeight(float height)
{
	ceilingHeight = height;
}

void Sector::setWallTopTexCoords(int index, float l, float r, float t, float b)
{
	walls[index].getTopTexCoords() = { l, r, t, b };
}

void Sector::setWallTopTexture(int index, const std::string& texName)
{
	walls[index].setTopTexture(texName);
}

void Sector::setWallMiddleTexCoords(int index, float l, float r, float t, float b)
{
	walls[index].getMidTexCoords() = { l, r, t, b };
}

void Sector::setWallMiddleTexture(int index, const std::string& texName)
{
	walls[index].setMidTexture(texName);
}

void Sector::setWallBottomTexCoords(int index, float l, float r, float t, float b)
{
	walls[index].getBottomTexCoords() = { l, r, t, b };
}

void Sector::setWallBottomTexture(int index, const std::string& texName)
{
	walls[index].setBottomTexture(texName);
}

void Sector::setFloorTex(const std::string& texName)
{
	floorTexName = texName;
}
void Sector::setCeilingTex(const std::string& texName)
{
	ceilingTexName = texName;
}

int Sector::getNumberOfWalls() const
{
	return walls.size();
}

SectorWall& Sector::getWall(int index)
{
	return walls[index];
}

const SectorWall& Sector::getWall(int index) const
{
	return walls[index];
}
