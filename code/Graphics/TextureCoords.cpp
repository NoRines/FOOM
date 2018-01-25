#include "TextureCoords.h"

void TextureCoords::cutFromLeftSide(float amount)
{
	left += amount;
}

void TextureCoords::cutFromRightSide(float amount)
{
	right -= amount;
}
