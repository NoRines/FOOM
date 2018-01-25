#include "Bitmap.h"
#include <algorithm>
#include <fstream>

Bitmap::Bitmap() :
width(0),
height(0),
components(nullptr)
{
}

Bitmap::Bitmap(int width, int height) :
width(width),
height(height),
components(new uint8_t[width*height*bpp])
{
}

Bitmap::Bitmap(const Bitmap& b) :
width(b.width),
height(b.height),
components(new uint8_t[width*height*bpp])
{
	std::copy(b.components, b.components + (width*height*bpp), components);
}

Bitmap& Bitmap::operator=(const Bitmap& b)
{
	Bitmap tmp = b;
	std::swap(tmp.width, width);
	std::swap(tmp.height, height);
	std::swap(tmp.components, components);
	return *this;
}

Bitmap::Bitmap(Bitmap&& b) :
width(b.width),
height(b.height),
components(b.components)
{
	b.components = nullptr;
}

Bitmap& Bitmap::operator=(Bitmap&& b)
{
	std::swap(b.width, width);
	std::swap(b.height, height);
	std::swap(b.components, components);
	return *this;
}

Bitmap::~Bitmap()
{
	delete[] components;
}

void Bitmap::clear(uint8_t shade)
{
	std::fill(components, components + width*height*bpp, shade);
}

void Bitmap::copyToByteArray(uint8_t* array, int pitch) const
{
	uint8_t* row = components;
	int bitmapPitch = width * bpp;

	for(int i = 0; i < height; i++)
	{
		std::copy(row, row + bitmapPitch, array);
		array += pitch;
		row += bitmapPitch;
	}
}

void Bitmap::drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	int index = (x + y * width) * bpp;
	components[index    ] = b;
	components[index + 1] = g;
	components[index + 2] = r;
	components[index + 3] = 0xFF;
}

void Bitmap::drawPixel(int x, int y, uint32_t color)
{
	*((uint32_t*)(components) + x + y * width) = color;
}

uint32_t Bitmap::getPixelColor(int x, int y) const
{
	if(x < 0 || x >= width || y < 0 || y >= height)
	{
		return 0;
	}
	return *((uint32_t*)(components) + x + y * width);
}

void Bitmap::copyPixel(int destX, int destY, int srcX, int srcY, const Bitmap& bitmap)
{
	int indexDest = (destX + destY * width) * bpp;
	int indexSrc = (srcX + srcY * bitmap.width) * bpp;

	components[indexDest    ] = bitmap.components[indexSrc    ];
	components[indexDest + 1] = bitmap.components[indexSrc + 1];
	components[indexDest + 2] = bitmap.components[indexSrc + 2];
	components[indexDest + 3] = bitmap.components[indexSrc + 3];
}

int Bitmap::getWidth() const
{
	return width;
}

int Bitmap::getHeight() const
{
	return height;
}

bool Bitmap::isValid() const
{
	if(components == nullptr)
	{
		return false;
	}
	return true;
}

Bitmap Bitmap::loadFromBMPFile(const char* filePath)
{
	std::ifstream file(filePath, std::ifstream::binary | std::ifstream::ate);

	if(!file.is_open())
	{
		//TODO: Log error
		return Bitmap();
	}

	int fileSize = file.tellg();
	file.seekg(0, file.beg);

	char* buffer = new char[fileSize];
	file.read(buffer, fileSize);
	file.close();


	uint8_t* bufWalker = (uint8_t*)buffer;

	if(bufWalker[0] != 'B' || bufWalker[1] != 'M')
	{
		delete[] buffer;
		return Bitmap();
	}

	bufWalker += 10;

	int32_t pixelDataOffset = *((int32_t*)&bufWalker[0]);
	bufWalker += 8;

	int32_t width = *((int32_t*)&bufWalker[0]);
	bufWalker += 4;
	int32_t height = *((int32_t*)&bufWalker[0]);
	bufWalker += 6;

	int16_t bitsPerPixel = *((int16_t*)&bufWalker[0]);

	if(bitsPerPixel != 24 && bitsPerPixel != 32)
	{
		delete[] buffer;
		return Bitmap();
	}

	int rowSize = ((bitsPerPixel * width + 31) / 32) * 4;

	Bitmap tmp(width, height);

	uint8_t* row = (uint8_t*)(buffer + pixelDataOffset);
	for(int y = 0; y < height; y++)
	{
		uint8_t* pixel = row;
		for(int x = 0; x < width; x++)
		{
			if(bitsPerPixel == 24)
			{
				uint32_t color = (0xFF<<24) | (pixel[2]<<16) | (pixel[1]<<8) | (pixel[0]);
				pixel += 3;
				tmp.drawPixel(x, height-(y+1), color);
			}
			else if(bitsPerPixel == 32)
			{
				uint32_t color = (pixel[3]<<24) | (pixel[2]<<16) | (pixel[1]<<8) | pixel[0];
				pixel += 4;
				tmp.drawPixel(x, height-(y+1), color);
			}
		}
		row += rowSize;
	}

	delete[] buffer;

	return tmp;
}
