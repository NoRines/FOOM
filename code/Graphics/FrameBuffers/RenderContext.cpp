#include "RenderContext.h"
#include <cmath>
#include <algorithm>

#include "../GraphicsConstants.h"

#include "../../Entities/Camera.h"

#include "../ScreenCoords.h"


RenderContext::RenderContext(int width, int height) :
Bitmap(width, height),
overBoundBuffer(new int[width]),
underBoundBuffer(new int[width])
{
}

RenderContext::~RenderContext()
{
	delete[] overBoundBuffer;
	delete[] underBoundBuffer;
}

void RenderContext::drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b)
{
	const int width = getWidth();
	const int height = getHeight();

	if(std::abs(x2-x1) >= std::abs(y2-y1))
	{
		if(x1 > x2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		int64_t xDist = x2 - x1;
		int64_t yDist = y2 - y1;
		for(int64_t x = x1; x < x2; x++)
		{
			int y = (((yDist << 16) / xDist) * (x - x1) + (y1 << 16)) >> 16;
			if(x < 0 || x >= width || y < 0 || y >= height)
			{
				continue;
			}
			drawPixel(x, y, r, g, b);
		}
	}
	else
	{
		if(y1 > y2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		int64_t xDist = x2 - x1;
		int64_t yDist = y2 - y1;
		for(int64_t y = y1; y < y2; y++)
		{
			int x = (((xDist << 16) / yDist) * (y - y1) + (x1 << 16)) >> 16;
			if(x < 0 || x >= width || y < 0 || y >= height)
			{
				continue;
			}
			drawPixel(x, y, r, g, b);
		}
	}
}

void RenderContext::resetScanLineAndBuffers()
{
	int width = getWidth();
	scanLine.clear();
	scanLine.addBound(-100000, 0);
	scanLine.addBound(width, 100000 + width);
	std::fill(overBoundBuffer, overBoundBuffer + width, 0);
	std::fill(underBoundBuffer, underBoundBuffer + width, getHeight());
}

bool RenderContext::shouldDraw() const
{
	if(scanLine.getNumberOfBounds() == 1)
	{
		return false;
	}
	return true;
}

void RenderContext::fillWallSegment(ScreenCoords& screenCoords,
			float u1, float u2, float v1, float v2, float oneOverZ1, float oneOverZ2,
			const Bitmap& wallTexture, const Bitmap& floorTexture, const Bitmap& ceilingTexture,
			bool underWindow, bool overWindow, float underHeight, float overHeight, const Camera& camera)
{
	// Divide the tex coords by the z coord
	u1 *= oneOverZ1;
	u2 *= oneOverZ2;

	// Calculate the step for the top an bottom edges
	float yStepOver = (float)(screenCoords.yO2 - screenCoords.yO1) / (float)(screenCoords.x2 - screenCoords.x1);
	float yStepUnder = (float)(screenCoords.yU2 - screenCoords.yU1) / (float)(screenCoords.x2 - screenCoords.x1);

	// Set start values for the y top and bottom values
	float yOverValue = screenCoords.yO1;
	float yUnderValue = screenCoords.yU1;

	// Store the width and height of the texture
	const int texWidth = wallTexture.getWidth();
	const int texHeight = wallTexture.getHeight();

	// Calculate where to start the tex coord and how much to step in x direction
	float xTex = u1;
	float xTexStep = (u2 - u1) / (float)(screenCoords.x2 - screenCoords.x1);

	// The 1/z also needs to be linearly interpolated
	float oneOverZ = oneOverZ1;
	float oneOverZStep = (oneOverZ2 - oneOverZ1) / (float)(screenCoords.x2 - screenCoords.x1);


	const int height = getHeight();


	int minScanIndex;
	int maxScanIndex;
	int xJump;

	for(int x = screenCoords.x1; x < screenCoords.x2; x++)
	{
		// TODO: Detta kan optimizeras mer sedan genom att göra så att getBoundMinIndex och getBoundMaxIndex inte behövs kallas varje kolumn
		minScanIndex = scanLine.getBoundMinIndex(x);
		maxScanIndex = scanLine.getBoundMaxIndex(x);
		if(minScanIndex != maxScanIndex)
		{
			xJump = scanLine.getMax(maxScanIndex) - x;
			x += xJump;
			if(x >= screenCoords.x2)
			{
				break;
			}

			yOverValue += (float)(yStepOver * xJump);
			yUnderValue += (float)(yStepUnder * xJump);
			xTex += (float)(xTexStep * xJump);
			oneOverZ += (float)(oneOverZStep * xJump);
		}
		drawWallColumn(
			x,
			(int)yOverValue,
			(int)yUnderValue,
			(int)((xTex / oneOverZ) * texWidth),
			(int)(v1 * texHeight),
			(int)(v2 * texHeight),
			wallTexture,
			texWidth,
			texHeight);

		drawFloorAndCeilingColumn(
			x,
			(int)yOverValue,
			(int)yUnderValue,
			!underWindow,
			!overWindow,
			underHeight,
			overHeight,
			floorTexture,
			ceilingTexture,
			camera);

		// Step all the values
		yOverValue += yStepOver;
		yUnderValue += yStepUnder;
		xTex += xTexStep;
		oneOverZ += oneOverZStep;

		if(underWindow)
		{
			if(underBoundBuffer[x] >yOverValue)
			{
				underBoundBuffer[x] = (yOverValue > height) ? height : yOverValue;
			}
		}
		else if(overWindow)
		{
			if(overBoundBuffer[x] < yUnderValue)
			{
				overBoundBuffer[x] = (yUnderValue < 0) ? 0 : yUnderValue;
			}
		}
	}

	if(!underWindow && !overWindow)
	{
		scanLine.addBound(screenCoords.x1, screenCoords.x2);
	}
}

void RenderContext::drawWallColumn(int xDest, int yMinDest, int yMaxDest,
			int xSrc, int yMinSrc, int yMaxSrc,
			const Bitmap& texture, int wallTexWidth, int wallTexHeight)
{
	if(yMinDest >= yMaxDest) // Return if the for loop will not be run
	{
		return;
	}

	// This is a preformence critical function so fixed point math is used

	// This macro speeds up the mod operation
	#define mod(val, ceil) \
		val >= ceil ? val % ceil : val

	// To step in y direction of the texture
	int64_t ySrc = (yMinSrc << 16);
	int64_t ySrcStep = (((yMaxSrc - yMinSrc) << 16) / (yMaxDest - yMinDest));


	if(yMinDest < overBoundBuffer[xDest])
	{
		ySrc += ySrcStep * ((yMinDest * (-1)) + overBoundBuffer[xDest]); // Make sure to offset incase y min is off the screen
		yMinDest = overBoundBuffer[xDest];
	}
	if(yMaxDest > underBoundBuffer[xDest])
	{
		yMaxDest = underBoundBuffer[xDest]; // Do not go outside of the screen
	}

	for(int yDest = yMinDest; yDest < yMaxDest; yDest++)
	{
		copyPixel(
			xDest,
			yDest,
			mod(xSrc, wallTexWidth),
			mod((ySrc>>16), wallTexHeight),
			texture);

		// Step along the texture
		ySrc += ySrcStep;
	}
}

void RenderContext::drawFloorAndCeilingColumn(int xDest, int yMinDest, int yMaxDest,
 			bool drawOver, bool drawUnder, float underHeight, float overHeight,
			const Bitmap& floorTexture, const Bitmap& ceilingTexture, const Camera& camera)
{
	// This is a stupid solution
	const int height = getHeight();
	const int width = getWidth();

	const int ceilingTexWidth = ceilingTexture.getWidth();
	const int ceilingTexHeight = ceilingTexture.getHeight();

	const int floorTexWidth = floorTexture.getWidth();
	const int floorTexHeight = floorTexture.getHeight();

	const float vfov = wallHeightScale * height;

	float xNominator;
	float xDenominator = (height / 2) - (camera.getVDirection() * vfov);
	Vector2f cameraPos = camera.getPosition();

	float psin = sin(camera.getHDirection());
	float pcos = cos(camera.getHDirection());

	float tmpX, tmpY;

	if(drawOver)
	{
		int bound = yMinDest;
		if(bound > underBoundBuffer[xDest])
		{
			bound = underBoundBuffer[xDest];
		}
		xNominator = overHeight * vfov;

		Vector2f relativeNearCoord;
		relativeNearCoord.x = xNominator / (xDenominator - overBoundBuffer[xDest]);
		relativeNearCoord.y = ((xDest - (width / 2)) * (tanHalfHFov * relativeNearCoord.x)) / (width / 2);

		Vector2f worldNearCoord;
		tmpX = relativeNearCoord.x * pcos - relativeNearCoord.y * psin;
		tmpY = relativeNearCoord.x * psin + relativeNearCoord.y * pcos;
		worldNearCoord.x = tmpX;
		worldNearCoord.y = tmpY;
		worldNearCoord += cameraPos;

		Vector2f relativeFarCoord;
		relativeFarCoord.x = xNominator / (xDenominator - bound);
		relativeFarCoord.y = ((xDest - (width / 2)) * (tanHalfHFov * relativeFarCoord.x)) / (width / 2);

		Vector2f worldFarCoord;
		tmpX = relativeFarCoord.x * pcos - relativeFarCoord.y * psin;
		tmpY = relativeFarCoord.x * psin + relativeFarCoord.y * pcos;
		worldFarCoord.x = tmpX;
		worldFarCoord.y = tmpY;
		worldFarCoord += cameraPos;

		float oneOverZNear = 1.0f / relativeNearCoord.x;
		float oneOverZFar = 1.0f / relativeFarCoord.x;
		worldNearCoord *= oneOverZNear;
		worldFarCoord *= oneOverZFar;

		Vector2f texCoord = worldNearCoord;
		Vector2f texStep = (worldFarCoord - worldNearCoord) / (float)(bound - overBoundBuffer[xDest]);

		float oneOverZ = oneOverZNear;
		float oneOverZStep = (oneOverZFar - oneOverZNear) / (float)(bound - overBoundBuffer[xDest]);

		for(int yDest = overBoundBuffer[xDest]; (yDest < bound && yDest < height); yDest++)
		{
			copyPixel(
				xDest,
				yDest,
				std::abs((int)((texCoord.x / oneOverZ) * ceilingTexWidth) % ceilingTexWidth),
				std::abs((int)((texCoord.y / oneOverZ) * ceilingTexHeight) % ceilingTexHeight),
				ceilingTexture);
			texCoord += texStep;
			oneOverZ += oneOverZStep;
		}
	}

	if(drawUnder)
	{
		int start = yMaxDest;
		if(start < 0)
		{
			start = 0;
		}
		xNominator = underHeight * vfov;

		Vector2f relativeFarCoord;
		relativeFarCoord.x = xNominator / (xDenominator - start);
		relativeFarCoord.y = ((xDest - (width / 2)) * (tanHalfHFov * relativeFarCoord.x)) / (width / 2);

		Vector2f worldFarCoord;
		tmpX = relativeFarCoord.x * pcos - relativeFarCoord.y * psin;
		tmpY = relativeFarCoord.x * psin + relativeFarCoord.y * pcos;
		worldFarCoord.x = tmpX;
		worldFarCoord.y = tmpY;
		worldFarCoord += cameraPos;

		Vector2f relativeNearCoord;
		relativeNearCoord.x = xNominator / (xDenominator - underBoundBuffer[xDest]);
		relativeNearCoord.y = ((xDest - (width / 2)) * (tanHalfHFov * relativeNearCoord.x)) / (width / 2);

		Vector2f worldNearCoord;
		tmpX = relativeNearCoord.x * pcos - relativeNearCoord.y * psin;
		tmpY = relativeNearCoord.x * psin + relativeNearCoord.y * pcos;
		worldNearCoord.x = tmpX;
		worldNearCoord.y = tmpY;
		worldNearCoord += cameraPos;

		float oneOverZFar = 1.0f / relativeFarCoord.x;
		float oneOverZNear = 1.0f / relativeNearCoord.x;
		worldFarCoord *= oneOverZFar;
		worldNearCoord *= oneOverZNear;

		Vector2f texCoord = worldFarCoord;
		Vector2f texCoordStep = (worldNearCoord - worldFarCoord) / (float)(underBoundBuffer[xDest] - start);

		float oneOverZ = oneOverZFar;
		float oneOverZStep = (oneOverZNear - oneOverZFar) / (float)(underBoundBuffer[xDest] - start);

		for(int yDest = start; (yDest < underBoundBuffer[xDest] && yDest < height); yDest++)
		{
			copyPixel(
				xDest,
				yDest,
				std::abs((int)((texCoord.x / oneOverZ) * floorTexWidth) % floorTexWidth),
				std::abs((int)((texCoord.y / oneOverZ) * floorTexHeight) % floorTexHeight),
				floorTexture);
			texCoord += texCoordStep;
			oneOverZ += oneOverZStep;
		}
	}
}
