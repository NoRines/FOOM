#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "RenderContext.h"

class Wall;
struct Vector2f;
class Camera;
struct ScreenCoords;

class GameRenderer : public RenderContext
{
public:
	GameRenderer(int width, int height);

	virtual ~GameRenderer() = default;

	GameRenderer(const GameRenderer& rhs) = delete;
	GameRenderer& operator=(const GameRenderer& rhs) = delete;
	GameRenderer(GameRenderer&& rhs) = delete;
	GameRenderer& operator=(GameRenderer&& rhs) = delete;

	void drawWall(const Wall& wall, const Camera& camera, const Bitmap& sectorFloorTex, const Bitmap& sectorCeilingTex);

	void setFloorCeilingHeight(float floor, float ceiling);

	void setIsUnderWindow(bool value);
	void setIsOverWindow(bool value);

private:
	void produceScreenCoords(ScreenCoords& screenCoords, float& leftTex, float& rightTex,
		bool& onScreen, Vector2f& point1, Vector2f& point2, const Wall& wall, const Camera& camera);

	float floorHeight;
	float ceilingHeight;
	bool underWindow;
	bool overWindow;
	Bitmap* defaultTexture;
};

#endif
