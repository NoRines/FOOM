#include "Wall.h"
#include "../Graphics/TextureManager.h"

Wall::Wall(const Vector2f& p1, const Vector2f& p2) :
point1(p1),
point2(p2)
{
	calculateNormal();
}

TextureCoords& Wall::getTopTexCoords()
{
	return topTexCoords;
}

TextureCoords& Wall::getMidTexCoords()
{
	return midTexCoords;
}

TextureCoords& Wall::getBottomTexCoords()
{
	return bottomTexCoords;
}

const TextureCoords& Wall::getTopTexCoords() const
{
	return topTexCoords;
}

const TextureCoords& Wall::getMidTexCoords() const
{
	return midTexCoords;
}

const TextureCoords& Wall::getBottomTexCoords() const
{
	return bottomTexCoords;
}

const Vector2f& Wall::getPoint1() const
{
	return point1;
}

const Vector2f& Wall::getPoint2() const
{
	return point2;
}

const Vector2f& Wall::getNormal() const
{
	return normal;
}

void Wall::setPoint1(const Vector2f& vec)
{
	point1 = vec;
}

void Wall::setPoint2(const Vector2f& vec)
{
	point2 = vec;
}

void Wall::setTopTexture(const std::string& texName)
{
	topTexName = texName;
	topTexture = TextureManager::get().loadTexture(topTexName);
}

void Wall::setMidTexture(const std::string& texName)
{
	midTexName = texName;
	midTexture = TextureManager::get().loadTexture(midTexName);
}

void Wall::setBottomTexture(const std::string& texName)
{
	bottomTexName = texName;
	bottomTexture = TextureManager::get().loadTexture(bottomTexName);
}

const std::string& Wall::getTopTextureName() const
{
	return topTexName;
}

const std::string& Wall::getMidTextureName() const
{
	return midTexName;
}

const std::string& Wall::getBottomTextureName() const
{
	return bottomTexName;
}

const Bitmap* Wall::getTopTexture() const
{
	return topTexture;
}

const Bitmap* Wall::getMidTexture() const
{
	return midTexture;
}

const Bitmap* Wall::getBottomTexture() const
{
	return bottomTexture;
}

void Wall::calculateNormal()
{
	normal = (point1 - point2).getUnit();
	normal.rotate(PI / 2.0f);
}

void Wall::setTopTexCoords(const TextureCoords& coords)
{
	topTexCoords = coords;
}

void Wall::setMidTexCoords(const TextureCoords& coords)
{
	midTexCoords = coords;
}

void Wall::setBottomTexCoords(const TextureCoords& coords)
{
	bottomTexCoords = coords;
}
