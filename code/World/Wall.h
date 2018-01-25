#ifndef WALL_H
#define WALL_H

#include "../Maths/Math.h"
#include "../Graphics/TextureCoords.h"

#include <string>

class Sector;
class Bitmap;

class Wall
{
public:
	Wall() = default;
	Wall(const Vector2f& p1, const Vector2f& p2);

	TextureCoords& getTopTexCoords();
	TextureCoords& getMidTexCoords();
	TextureCoords& getBottomTexCoords();

	const TextureCoords& getTopTexCoords() const;
	const TextureCoords& getMidTexCoords() const;
	const TextureCoords& getBottomTexCoords() const;

	const Vector2f& getPoint1() const;
	const Vector2f& getPoint2() const;
	const Vector2f& getNormal() const;

	void setPoint1(const Vector2f& vec);
	void setPoint2(const Vector2f& vec);

	void setTopTexture(const std::string& texName);
	void setMidTexture(const std::string& texName);
	void setBottomTexture(const std::string& texName);

	const std::string& getTopTextureName() const;
	const std::string& getMidTextureName() const;
	const std::string& getBottomTextureName() const;

	const Bitmap* getTopTexture() const;
	const Bitmap* getMidTexture() const;
	const Bitmap* getBottomTexture() const;

	void calculateNormal();

protected:
	void setTopTexCoords(const TextureCoords& coords);
	void setMidTexCoords(const TextureCoords& coords);
	void setBottomTexCoords(const TextureCoords& coords);

private:
	Vector2f point1;
	Vector2f point2;

	Vector2f normal;

	TextureCoords topTexCoords;
	std::string topTexName;
	Bitmap* topTexture = nullptr;

	TextureCoords midTexCoords;
	std::string midTexName;
	Bitmap* midTexture = nullptr;

	TextureCoords bottomTexCoords;
	std::string bottomTexName;
	Bitmap* bottomTexture = nullptr;
};

#endif
