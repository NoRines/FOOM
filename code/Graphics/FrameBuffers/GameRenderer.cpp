#include "GameRenderer.h"

#include <algorithm>

#include "../../World/Wall.h"
#include "../../Maths/Math.h"

#include "../GraphicsConstants.h"

#include "../../Entities/Camera.h"

#include "../ScreenCoords.h"

#include "../TextureManager.h"


GameRenderer::GameRenderer(int width, int height) :
RenderContext(width, height),
floorHeight(-1.0f),
ceilingHeight(1.0f),
underWindow(false),
overWindow(false),
defaultTexture(TextureManager::get().loadTexture("default"))
{
}

void GameRenderer::drawWall(const Wall& wall, const Camera& camera, const Bitmap& sectorFloorTex, const Bitmap& sectorCeilingTex)
{
	bool onScreen = true;
	ScreenCoords screenCoords;
	TextureCoords textureCoords;

	if(underWindow)
	{
		textureCoords = wall.getBottomTexCoords();
	}
	else if(overWindow)
	{
		textureCoords = wall.getTopTexCoords();
	}
	else
	{
		textureCoords = wall.getMidTexCoords();
	}

	Vector2f point1;
	Vector2f point2;

	produceScreenCoords(
		screenCoords,		// Reference to the screen space coords
		textureCoords.left,	// Reference to the left texture coord
		textureCoords.right,// Reference to the right texture coord
		onScreen,			// If this is false the wall should not be drawn
		point1,				// The rotated and translated wall point1
		point2,				// The rotated and translated wall point2
		wall,				// The actual wall
		camera);

	if(!onScreen || screenCoords.x1 == screenCoords.x2)
	{
		underWindow = false;
		overWindow = false;
		return;
	}

	const Bitmap* texture;
	if(overWindow)
	{
		texture = wall.getTopTexture();
	}
	else if(underWindow)
	{
		texture = wall.getBottomTexture();
	}
	else
	{
		texture = wall.getMidTexture();
	}

	const float cameraHeadPos = camera.getHeadPos();

	fillWallSegment(
		screenCoords,
		textureCoords.left,
		textureCoords.right,
		textureCoords.top,
		textureCoords.bottom,
		1.0f / point1.x,
		1.0f / point2.x,
		(texture != nullptr) ? *texture : *defaultTexture,
		sectorFloorTex,
		sectorCeilingTex,
		underWindow,
		overWindow,
		floorHeight - cameraHeadPos,
		ceilingHeight - cameraHeadPos,
		camera);

	underWindow = false;
	overWindow = false;
}

void GameRenderer::setFloorCeilingHeight(float floor, float ceiling)
{
	floorHeight = floor;
	ceilingHeight = ceiling;
}

void GameRenderer::setIsUnderWindow(bool value)
{
	underWindow = value;
}

void GameRenderer::setIsOverWindow(bool value)
{
	overWindow = value;
}

void GameRenderer::produceScreenCoords(ScreenCoords& screenCoords, float& leftTex,
	float& rightTex, bool& onScreen, Vector2f& point1, Vector2f& point2, const Wall& wall, const Camera& camera)
{
	constexpr float nearLimit = 0.01f;

	point1 = wall.getPoint1();
	point2 = wall.getPoint2();
	Vector2f normal = wall.getNormal();

	Vector2f cameraPos = camera.getPosition();

	float dist = distFromLine(cameraPos, point1, normal);

	if(dist > nearLimit)
	{
		onScreen = false;
		return;
	}

	const int width = getWidth();
	const int height = getHeight();

	const float vfov = wallHeightScale * height;

	point1 -= cameraPos;
	point2 -= cameraPos;

	point1.rotate(-camera.getHDirection());
	point2.rotate(-camera.getHDirection());

	if(point1.x < nearLimit && point2.x < nearLimit)
	{
		onScreen = false;
		return;
	}

	static const Vector2f leftBound(cos(-(hfov/2.0f)) * 10.0f, sin(-(hfov/2.0f)) * 10.0f);
	static const Vector2f leftNormal = leftBound.getUnit().rotate((float)PI/2.0f);
	static const Vector2f rightBound(cos((hfov/2.0f)) * 10.0f, sin((hfov/2.0f)) * 10.0f);
	static const Vector2f rightNormal = rightBound.getUnit().rotate(-(float)PI/2.0f);

	const float leftDist1 = distFromLine(point1, leftBound, leftNormal);
	const float leftDist2 = distFromLine(point2, leftBound, leftNormal);
	const float rightDist1 = distFromLine(point1, rightBound, rightNormal);
	const float rightDist2 = distFromLine(point2, rightBound, rightNormal);

	if((rightDist1 < 0.0f && rightDist2 < 0.0f) || (leftDist1 < 0.0f && leftDist2 < 0.0f))
	{
		onScreen = false;
		return;
	}

	float wallLength = (point1 - point2).length();
	Vector2f oldP1 = point1;
	Vector2f oldP2 = point2;
	float oldLeftTex = leftTex;
	float oldRightTex = rightTex;

	Vector2f intersection;
	if(lineSegmentIntersection({0.0f, 0.0f}, rightBound * 100.0f, point1, point2, intersection))
	{
		if(rightDist1 > 0.0f && rightDist2 < 0.0f)
		{
			point2 = intersection;
			rightTex -= ((oldP2 - point2).length() / wallLength) * (oldRightTex - oldLeftTex);
		}
	}
	if(lineSegmentIntersection({0.0f, 0.0f}, leftBound * 100.0f, point1, point2, intersection))
	{
		if(leftDist2 > 0.0f && leftDist1 < 0.0f)
		{
			point1 = intersection;
			leftTex += ((oldP1 - point1).length() / wallLength) * (oldRightTex - oldLeftTex);
		}
	}

	#define yaw(y, z) \
		(y + camera.getVDirection() * z)

	float xScale1 = point1.y / (tanHalfHFov * point1.x);
	float xScale2 = point2.y / (tanHalfHFov * point2.x);
	float yScale1 = vfov / point1.x;
	float yScale2 = vfov / point2.x;

	if(xScale2 < -0.999f)
	{
		xScale2 = -1.0f;
	}
	if(xScale1 > 0.999f)
	{
		xScale1 = 1.0f;
	}

	const float cameraHeadPos = camera.getHeadPos();

	screenCoords.x1 = (width/2) + (int)((float)(width/2) * xScale1);
	screenCoords.yO1 = (height/2) + (int)(yScale1 * -yaw((ceilingHeight - cameraHeadPos), point1.x));
	screenCoords.yU1 = (height/2) + (int)(yScale1 * -yaw((floorHeight - cameraHeadPos), point1.x));

	screenCoords.x2 = (width/2) + (int)((float)(width/2) * xScale2);
	screenCoords.yO2 = (height/2) + (int)(yScale2 * -yaw((ceilingHeight - cameraHeadPos), point2.x));
	screenCoords.yU2 = (height/2) + (int)(yScale2 * -yaw((floorHeight - cameraHeadPos), point2.x));

	if(screenCoords.x1 > screenCoords.x2)
	{
		std::swap(screenCoords.x1, screenCoords.x2);
		std::swap(screenCoords.yO1, screenCoords.yO2);
		std::swap(screenCoords.yU1, screenCoords.yU2);
		std::swap(point1, point2);
	}

	if(screenCoords.x1 < 0)
	{
		screenCoords.x1 = 0;
	}
	if(screenCoords.x2 > width)
	{
		screenCoords.x2 = width;
	}
}
