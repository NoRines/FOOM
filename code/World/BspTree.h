#ifndef BSPTREE_H
#define BSPTREE_H

#include "Sector.h"
#include "BspWall.h"

class GameRenderer;
class Bitmap;
class Camera;

class BspTree
{
public:
	BspTree();

	void loadBspTree(std::vector<Sector>& mapSectors);

	void drawBspTree(GameRenderer& gameRenderer, const Camera& camera);

	void collideWithMap(Camera& camera);

	int findSector(const Vector2f& point, int node = 0);

private:
	enum class PlaneInfo
	{
		FRONT,
		BACK,
		ON_PLANE,
		SPANNING_PLANE
	};

	struct BspNode
	{
		int frontNode;
		int backNode;
		bool isLeaf = false;
		int splitPlane;
		int sector;
	};

	struct SubSector // This is a convex area
	{
		float floorHeight;
		float ceilingHeight;

		int wallStartIndex;
		int wallEndIndex;

		std::string floorTexName;
		Bitmap* floorTexture;

		std::string ceilingTexName;
		Bitmap* ceilingTexture;
	};

	struct BuildWall
	{
		SectorWall wall;
		Sector* parentSector;
		bool isSplitter = false;
	};

	void drawTreeRecusive(int nodeIndex, GameRenderer& gameRenderer, const Camera& camera);

	void buildTree(int nodeIndex, std::vector<BuildWall>& buildWalls);

	bool isConvex(const std::vector<BuildWall>& buildWalls);

	int selectBestSplitter(std::vector<BuildWall>& buildWalls);

	void splitWall(const Wall& plane, BuildWall& wall, BuildWall& front, BuildWall& back);

	PlaneInfo classifyPoint(const Wall& plane, const Vector2f& point) const;
	PlaneInfo classifyWall(const Wall& plane, const Wall& wall) const;

	void increaseNumberOfWalls();
	void increaseNumberOfSectors();
	void increaseNumberOfNodes();
	void increaseNumberOfSplitPlanes();

	std::vector<BspWall> walls;
	int numWalls = 0;

	std::vector<SubSector> sectors;
	int numSectors = 0;

	std::vector<BspNode> nodes;
	int numNodes = 0;

	std::vector<Wall> splitPlanes;
	int numPlanes = 0;
};

#endif
