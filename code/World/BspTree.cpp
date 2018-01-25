#include "BspTree.h"
#include "../Maths/Math.h"
#include "../Graphics/FrameBuffers/GameRenderer.h"
#include "../Entities/Camera.h"
#include "../Graphics/TextureManager.h"

#include <iostream> // remove this include
#include "../Input.h" // remove this include

BspTree::BspTree()
{
	walls.resize(100);
	sectors.resize(100);
	nodes.resize(100);
	splitPlanes.resize(100);
}

void BspTree::loadBspTree(std::vector<Sector>& mapSectors)
{
	std::vector<BuildWall> buildWalls;

	for(int i = 0; i < mapSectors.size(); i++)
	{
		for(int j = 0; j < mapSectors[i].walls.size(); j++)
		{
			buildWalls.push_back({mapSectors[i].walls[j], &mapSectors[i]});
		}
	}

	buildTree(0, buildWalls);
}

void BspTree::drawBspTree(GameRenderer& gameRenderer, const Camera& camera)
{
	drawTreeRecusive(0, gameRenderer, camera);
}

void BspTree::collideWithMap(Camera& camera)
{
	int sector = camera.getCurrentSector();

	sector = findSector(camera.getPosition());
	camera.calculateHeadPos(sectors[sector].floorHeight);
}

int BspTree::findSector(const Vector2f& point, int node)
{
	if(node == -1)
	{
		return -1;
	}

	if(nodes[node].isLeaf)
	{
		return nodes[node].sector;
	}

	PlaneInfo playerInfo = classifyPoint(
		splitPlanes[nodes[node].splitPlane],
		point);

	if(playerInfo == PlaneInfo::FRONT)
	{
		return findSector(point, nodes[node].frontNode);
	}
	else
	{
		return findSector(point, nodes[node].backNode);
	}
}

void BspTree::drawTreeRecusive(
	int nodeIndex,
	GameRenderer& gameRenderer,
	const Camera& camera)
{
	if(!gameRenderer.shouldDraw())
	{
		return;
	}

	if(nodes[nodeIndex].isLeaf)
	{
		int currentSector = nodes[nodeIndex].sector;
		if(currentSector == -1)
		{
			return;
		}

		int startWall = sectors[currentSector].wallStartIndex;
		int endWall = sectors[currentSector].wallEndIndex;
		float floorLevel = sectors[currentSector].floorHeight;
		float ceilingLevel = sectors[currentSector].ceilingHeight;
		float nFloor;
		float nCeiling;

		gameRenderer.setFloorCeilingHeight(floorLevel, ceilingLevel);

		for(int i = startWall; i < endWall; i++)
		{
			if(walls[i].isWindow())
			{
				nFloor = walls[i].getNeighbourFloor();
				nCeiling = walls[i].getNeighbourCeiling();

				if(nFloor >= floorLevel)
				{
					gameRenderer.setFloorCeilingHeight(
						floorLevel,
						nFloor);
				}
				else
				{
					gameRenderer.setFloorCeilingHeight(
						floorLevel,
						floorLevel);
				}
				gameRenderer.setIsUnderWindow(true);
				gameRenderer.drawWall(
					walls[i],
					camera,
					*sectors[currentSector].floorTexture,
					*sectors[currentSector].ceilingTexture);
				

				if(nCeiling <= ceilingLevel)
				{
					gameRenderer.setFloorCeilingHeight(
						nCeiling,
						ceilingLevel);
				}
				else
				{
					gameRenderer.setFloorCeilingHeight(
						ceilingLevel,
						ceilingLevel);
				}
				gameRenderer.setIsOverWindow(true);
				gameRenderer.drawWall(
					walls[i],
					camera,
					*sectors[currentSector].floorTexture,
					*sectors[currentSector].ceilingTexture);

				gameRenderer.setFloorCeilingHeight(
					floorLevel,
					ceilingLevel);
			}
			else
			{
				gameRenderer.drawWall(
					walls[i],
					camera,
					*sectors[currentSector].floorTexture,
					*sectors[currentSector].ceilingTexture);
			}
		}
		return;
	}

	PlaneInfo playerInfo = classifyPoint(
		splitPlanes[nodes[nodeIndex].splitPlane],
		camera.getPosition());

	if(playerInfo == PlaneInfo::FRONT)
	{
		drawTreeRecusive(
			nodes[nodeIndex].frontNode,
			gameRenderer,
			camera);
		drawTreeRecusive(
			nodes[nodeIndex].backNode,
			gameRenderer,
			camera);
	}
	else
	{
		drawTreeRecusive(nodes[nodeIndex].backNode, gameRenderer, camera);
		drawTreeRecusive(nodes[nodeIndex].frontNode, gameRenderer, camera);
	}
}

void BspTree::buildTree(int nodeIndex, std::vector<BuildWall>& buildWalls)
{
	if(isConvex(buildWalls)) // Check if the wall set is convex
	{
		nodes[nodeIndex].isLeaf = true; // If the wall set is convex this means this is a leaf node

		if(!buildWalls.empty()) // Make sure that there are walls in the set
		{
			// Set the sector index for the node
			nodes[nodeIndex].sector = numSectors;
			// Where should the sector start with the walls
			sectors[numSectors].wallStartIndex = numWalls;
			// Get the floor and ceiling height for the sector
			sectors[numSectors].floorHeight = buildWalls[0].parentSector->floorHeight;
			sectors[numSectors].ceilingHeight = buildWalls[0].parentSector->ceilingHeight;
			// Get the floor and ceiling textures
			sectors[numSectors].floorTexName = buildWalls[0].parentSector->floorTexName;
			sectors[numSectors].floorTexture = TextureManager::get().loadTexture(sectors[numSectors].floorTexName);
			sectors[numSectors].ceilingTexName = buildWalls[0].parentSector->ceilingTexName;
			sectors[numSectors].ceilingTexture = TextureManager::get().loadTexture(sectors[numSectors].ceilingTexName);

			// For each wall copy to the wall vector
			for(auto& wall : buildWalls)
			{
				walls[numWalls] = wall.wall;
				increaseNumberOfWalls();
			}

			// Set where the sector should stop looking for walls
			sectors[numSectors].wallEndIndex = numWalls;
			increaseNumberOfSectors();
		}
		else
		{
			nodes[nodeIndex].sector = -1; // There are no walls so there is no sector
		}
		return; // We are now att a leaf so stop the recursion
	}

	// Create two vectors one for front walls and one for back walls
	std::vector<BuildWall> frontWalls;
	std::vector<BuildWall> backWalls;

	// Select the best split plane
	int bestSplitterIndex = selectBestSplitter(buildWalls);
	if(bestSplitterIndex == -1)
	{
		// This should not happen
	}

	
	nodes[nodeIndex].splitPlane = bestSplitterIndex;

	for(auto& wall : buildWalls)
	{
		PlaneInfo splitInfo = classifyWall(splitPlanes[bestSplitterIndex], wall.wall);

		switch(splitInfo)
		{
			case PlaneInfo::FRONT:
			{
				frontWalls.push_back(wall);
			} break;

			case PlaneInfo::BACK:
			{
				backWalls.push_back(wall);
			} break;

			case PlaneInfo::ON_PLANE:
			{
				Vector2f planeNormal = splitPlanes[bestSplitterIndex].getNormal();
				Vector2f wallNormal = wall.wall.getNormal();
				planeNormal.normalize();
				wallNormal.normalize();
				float dot = planeNormal.dot(wallNormal);
				if(dot > 0.0f)
				{
					frontWalls.push_back(wall);
				}
				else
				{
					backWalls.push_back(wall);
				}
			} break;

			case PlaneInfo::SPANNING_PLANE:
			{
				BuildWall frontWall;
				BuildWall backWall;
				splitWall(
					splitPlanes[bestSplitterIndex],
					wall,
					frontWall,
					backWall);

				frontWalls.push_back(frontWall);
				backWalls.push_back(backWall);
				std::cout << "Wall was split" << std::endl;
			} break;

			default:
			{} break;
		}
	}

	nodes[nodeIndex].frontNode = numNodes + 1;
	increaseNumberOfNodes();
	buildTree(numNodes, frontWalls);

	nodes[nodeIndex].backNode = numNodes + 1;
	increaseNumberOfNodes();
	buildTree(numNodes, backWalls);
}

bool BspTree::isConvex(const std::vector<BuildWall>& buildWalls)
{
	for(int i = 0; i < buildWalls.size(); i++)
	{
		for(int j = i + 1; j < buildWalls.size(); j++)
		{
			PlaneInfo p1 = classifyWall(buildWalls[i].wall, buildWalls[j].wall);
			PlaneInfo p2 = classifyWall(buildWalls[j].wall, buildWalls[i].wall);

			if(p1 == PlaneInfo::BACK || p1 == PlaneInfo::SPANNING_PLANE)
			{
				return false;
			}
			if(p2 == PlaneInfo::BACK || p2 == PlaneInfo::SPANNING_PLANE)
			{
				return false;
			}
		}
	}
	return true;
}

int BspTree::selectBestSplitter(std::vector<BuildWall>& buildWalls)
{
	// Count front back and splits for each wall/splitting plane
	int highScore = 0;
	int highScoreIndex = 0;
	bool firstTime = true; // This is set to true first time through the loop

	for(int i = 0; i < buildWalls.size(); i++)
	{
		int front = 0;
		int back = 0;
		int split = 0;
		if(buildWalls[i].isSplitter) // If the wall has been used it should not be considerd
		{
			continue;
		}

		for(int j = 0; j < buildWalls.size(); j++)
		{
			PlaneInfo splitInfo = classifyWall(buildWalls[i].wall, buildWalls[j].wall);

			switch(splitInfo)
			{
				case PlaneInfo::FRONT:
				{
					front++;
				} break;

				case PlaneInfo::BACK:
				{
					back++;
				} break;

				case PlaneInfo::SPANNING_PLANE:
				{
					front++;
					back++;
					split++;
				} break;

				default:
				{} break;
			}
		}
		int currentScore = std::abs(front - back) + (3 * split);
		if(firstTime)
		{
			firstTime = false;
			highScore = currentScore;
			highScoreIndex = i;
		}
		else if(highScore > currentScore)
		{
			highScore = currentScore;
			highScoreIndex = i;
		}
	}
	if(firstTime)
	{
		return -1;
	}
	splitPlanes[numPlanes] = buildWalls[highScoreIndex].wall;
	buildWalls[highScoreIndex].isSplitter = true;
	increaseNumberOfSplitPlanes();
	return (numPlanes - 1);
}

void BspTree::splitWall(const Wall& plane, BuildWall& wall, BuildWall& front, BuildWall& back)
{
	Vector2f intersect;
	Vector2f wallP1 = wall.wall.getPoint1();
	Vector2f wallP2 = wall.wall.getPoint2();
	float wallLength = (wallP1 - wallP2).length();
	float topTexScale = (wall.wall.getTopTexCoords().right - wall.wall.getTopTexCoords().left);
	float midTexScale = (wall.wall.getMidTexCoords().right - wall.wall.getMidTexCoords().left);
	float bottomTexScale = (wall.wall.getBottomTexCoords().right - wall.wall.getBottomTexCoords().left);

	lineIntersection(plane.getPoint1(), plane.getPoint2(), wallP1, wallP2, intersect);

	PlaneInfo p1 = classifyPoint(plane, wallP1);
	PlaneInfo p2 = classifyPoint(plane, wallP2);

	if(p1 == PlaneInfo::FRONT && p2 == PlaneInfo::BACK)
	{
		front = wall;
		back = wall;

		front.wall.setPoint1(wallP1);
		front.wall.setPoint2(intersect);
		front.wall.calculateNormal();

		float backLength = (intersect - wallP2).length();

		front.wall.getTopTexCoords().cutFromRightSide((backLength / wallLength) * topTexScale);
		front.wall.getMidTexCoords().cutFromRightSide((backLength / wallLength) * midTexScale);
		front.wall.getBottomTexCoords().cutFromRightSide((backLength / wallLength) * bottomTexScale);

		back.wall.setPoint1(intersect);
		back.wall.setPoint2(wallP2);
		back.wall.calculateNormal();

		float frontLength = (wallP1 - intersect).length();

		back.wall.getTopTexCoords().cutFromLeftSide((frontLength / wallLength) * topTexScale);
		back.wall.getMidTexCoords().cutFromLeftSide((frontLength / wallLength) * midTexScale);
		back.wall.getBottomTexCoords().cutFromLeftSide((frontLength / wallLength) * bottomTexScale);
	}
	else if(p1 == PlaneInfo::BACK && p2 == PlaneInfo::FRONT)
	{
		front = wall;
		back = wall;

		back.wall.setPoint1(wallP1);
		back.wall.setPoint2(intersect);
		back.wall.calculateNormal();

		float frontLength = (wallP2 - intersect).length();

		back.wall.getTopTexCoords().cutFromRightSide((frontLength / wallLength) * topTexScale);
		back.wall.getMidTexCoords().cutFromRightSide((frontLength / wallLength) * midTexScale);
		back.wall.getBottomTexCoords().cutFromRightSide((frontLength / wallLength) * bottomTexScale);

		front.wall.setPoint1(intersect);
		front.wall.setPoint2(wallP2);
		front.wall.calculateNormal();

		float backLength = (wallP1 - intersect).length();

		front.wall.getTopTexCoords().cutFromLeftSide((backLength / wallLength) * topTexScale);
		front.wall.getMidTexCoords().cutFromLeftSide((backLength / wallLength) * midTexScale);
		front.wall.getBottomTexCoords().cutFromLeftSide((backLength / wallLength) * bottomTexScale);
	}
}

BspTree::PlaneInfo BspTree::classifyPoint(const Wall& plane, const Vector2f& point) const
{
	float result = distFromLine(point, plane.getPoint1(), plane.getNormal());

	if(result > 0.001f)
	{
		return PlaneInfo::BACK;
	}
	else if(result < -0.001f)
	{
		return PlaneInfo::FRONT;
	}
	else
	{
		return PlaneInfo::ON_PLANE;
	}
}

BspTree::PlaneInfo BspTree::classifyWall(const Wall& plane, const Wall& wall) const
{
	PlaneInfo p1 = classifyPoint(plane, wall.getPoint1());
	PlaneInfo p2 = classifyPoint(plane, wall.getPoint2());

	if(p1 == p2)
	{
		if(p1 == PlaneInfo::FRONT)
		{
			return PlaneInfo::FRONT;
		}
		else if(p1 == PlaneInfo::BACK)
		{
			return PlaneInfo::BACK;
		}
		else
		{
			return PlaneInfo::ON_PLANE;
		}
	}

	if(p1 == PlaneInfo::ON_PLANE || p2 == PlaneInfo::ON_PLANE)
	{
		if(p1 == PlaneInfo::FRONT || p2 == PlaneInfo::FRONT)
		{
			return PlaneInfo::FRONT;
		}
		else if(p1 == PlaneInfo::BACK || p2 == PlaneInfo::BACK)
		{
			return PlaneInfo::BACK;
		}
	}

	return PlaneInfo::SPANNING_PLANE;
}

void BspTree::increaseNumberOfWalls()
{
	numWalls++;
	while(numWalls >= walls.size())
	{
		int oldSize = walls.size();
		walls.resize(oldSize + 100);
	}
}

void BspTree::increaseNumberOfSectors()
{
	numSectors++;
	while(numSectors >= sectors.size())
	{
		int oldSize = sectors.size();
		sectors.resize(oldSize + 100);
	}
}

void BspTree::increaseNumberOfNodes()
{
	numNodes++;
	while(numNodes >= nodes.size())
	{
		int oldSize = nodes.size();
		nodes.resize(oldSize + 100);
	}
}

void BspTree::increaseNumberOfSplitPlanes()
{
	numPlanes++;
	while(numPlanes >= splitPlanes.size())
	{
		int oldSize = splitPlanes.size();
		splitPlanes.resize(oldSize + 100);
	}
}
