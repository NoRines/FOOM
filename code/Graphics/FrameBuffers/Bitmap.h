#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>

//#define BYTES_PER_PIXEL 4
//#define bpp BYTES_PER_PIXEL
static constexpr int BYTES_PER_PIXEL = 4;
static constexpr int bpp = BYTES_PER_PIXEL;

class Bitmap
{
public:
	Bitmap(int width, int height);

	Bitmap(const Bitmap& b);
	Bitmap& operator=(const Bitmap& b);
	Bitmap(Bitmap&& b);
	Bitmap& operator=(Bitmap&& b);

	virtual ~Bitmap();

	void clear(uint8_t shade);

	void copyToByteArray(uint8_t* array, int pitch) const;

	void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void drawPixel(int x, int y, uint32_t color);

	uint32_t getPixelColor(int x, int y) const;

	void copyPixel(int destX, int destY, int srcX, int srcY, const Bitmap& bitmap);

	int getWidth() const;
	int getHeight() const;

	bool isValid() const;

	static Bitmap loadFromBMPFile(const char* filePath);

private:
	Bitmap();

	int width;
	int height;
	uint8_t* components;
};

#endif
