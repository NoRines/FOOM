#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include "Bitmap.h"

#include "../ScanLine.h"

class Vector2f;
class Camera;
struct ScreenCoords;

class RenderContext : public Bitmap
{
public:
	RenderContext(int width, int height);

	virtual ~RenderContext();

	RenderContext(const RenderContext& rhs) = delete;
	RenderContext& operator=(const RenderContext& rhs) = delete;
	RenderContext(RenderContext&& rhs) = delete;
	RenderContext& operator=(RenderContext&& rhs) = delete;

	void drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b);


	void resetScanLineAndBuffers();

	bool shouldDraw() const;

protected:
	void fillWallSegment(ScreenCoords& screenCoords,
			float u1, float u2, float v1, float v2, float oneOverZ1, float oneOverZ2,
			const Bitmap& wallTexture, const Bitmap& floorTexture, const Bitmap& ceilingTexture,
			bool underWindow, bool overWindow, float underHeight, float overHeight, const Camera& camera);

private:
	void drawWallColumn(int xDest, int yMinDest, int yMaxDest,
			int xSrc, int yMinSrc, int yMaxSrc,
			const Bitmap& texture, int wallTexWidth, int wallTexHeight);

	void drawFloorAndCeilingColumn(int xDest, int yMinDest, int yMaxDest,
				bool drawOver, bool drawUnder, float underHeight, float overHeight,
				const Bitmap& floorTexture, const Bitmap& ceilingTexture, const Camera& camera);

	ScanLine scanLine;
	int* overBoundBuffer;
	int* underBoundBuffer;
};

#endif
