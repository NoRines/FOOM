#ifndef TEXTURECOORDS_H
#define TEXTURECOORDS_H

struct TextureCoords
{
	float left = 0.0f;
	float right = 1.0f;
	float top = 0.0f;
	float bottom = 1.0f;

	void cutFromLeftSide(float amount);
	void cutFromRightSide(float amount);
};

#endif
