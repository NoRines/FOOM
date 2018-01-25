#ifndef SECTOR_H
#define SECTOR_H

#include <vector>
#include "SectorWall.h"

/// This class should hold a set of walls that enclose a
/// nonconvex area

class BspTree;

class Sector
{
public:
	friend BspTree;

	Sector();
	Sector(float floorHeight, float ceilingHeight);

	void addWall(const SectorWall& wall);

	float getFloorHeight() const;
	float getCeilingHeight() const;

	void setFloorHeight(float height);
	void setCeilingHeight(float height);

	void setWallTopTexCoords(int index, float l, float r, float t, float b);
	void setWallTopTexture(int index, const std::string& texName);

	void setWallMiddleTexCoords(int index, float l, float r, float t, float b);
	void setWallMiddleTexture(int index, const std::string& texName);

	void setWallBottomTexCoords(int index, float l, float r, float t, float b);
	void setWallBottomTexture(int index, const std::string& texName);

	void setFloorTex(const std::string& texName);
	void setCeilingTex(const std::string& texName);

	int getNumberOfWalls() const;
	SectorWall& getWall(int index);
	const SectorWall& getWall(int index) const;

private:
	std::string floorTexName;
	std::string ceilingTexName;

	float floorHeight;
	float ceilingHeight;

	std::vector<SectorWall> walls;
};

#endif
