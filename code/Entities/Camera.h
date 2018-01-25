#ifndef CAMERA_H
#define CAMERA_H

#include "../Maths/Math.h"

class Camera
{
public:
	Camera(const Vector2f& position);

	void update(float delta);

	void move(const Vector2f& moveVec);

	const Vector2f& getPosition() const;

	float getHDirection() const;
	float getVDirection() const;

	float getHeadHeight() const;

	void calculateHeadPos(float floorHeight);

	float getHeadPos() const;

	int getCurrentSector() const;
	void setCurrentSector(int sector);

private:
	Vector2f position;
	float hDirection;
	float vDirection;
	bool grabScreen;
	float headHeight;
	float headPos;
	int currentSector;
};

#endif
