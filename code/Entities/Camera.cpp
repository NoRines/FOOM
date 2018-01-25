#include "Camera.h"

#include "../Input.h"
#include "../Display.h"

Camera::Camera(const Vector2f& position) :
position(position),
hDirection(0.0f),
vDirection(0.0f),
grabScreen(false),
headHeight(1.0f),
headPos(0.0f),
currentSector(0)
{
}

void Camera::update(float delta)
{
	Vector2f moveVec;

	if(Input::get().isKeyDown(Input::Keyboard::W))
	{
		moveVec += Vector2f(cos(hDirection), sin(hDirection));
	}
	if(Input::get().isKeyDown(Input::Keyboard::S))
	{
		moveVec -= Vector2f(cos(hDirection), sin(hDirection));
	}
	if(Input::get().isKeyDown(Input::Keyboard::A))
	{
		moveVec -= Vector2f(sin(-hDirection), cos(hDirection));
	}
	if(Input::get().isKeyDown(Input::Keyboard::D))
	{
		moveVec += Vector2f(sin(-hDirection), cos(hDirection));
	}

	if(moveVec.length() > 0.001f)
	{
		moveVec.normalize();
		move(moveVec * delta);
	}

	if(Input::get().isKeyPressed(Input::Keyboard::ESCAPE))
	{
		grabScreen = !grabScreen;
		if(grabScreen)
		{
			Input::get().hideMouse(true);
		}
		else
		{
			Input::get().hideMouse(false);
		}
	}

	if(grabScreen)
	{
		int windowWidth;
		int windowHeight;
		Display::get().getWindowSize(windowWidth, windowHeight);
		int relativeX = (windowWidth / 2) - Input::get().getMouseX();
		int relativeY = (windowHeight / 2) - Input::get().getMouseY();
		Input::get().setMousePosToMiddleOfScreen(Display::get());
		hDirection -= relativeX * 0.001f;
		vDirection -= relativeY * 0.01f;

		constexpr float maxYaw = 2 * PI;

		if(vDirection > maxYaw)
		{
			vDirection = maxYaw;
		}
		if(vDirection < -maxYaw)
		{
			vDirection = -maxYaw;
		}

		while(hDirection < -PI)
		{
			hDirection += 2 * PI;
		}
		while(hDirection > PI)
		{
			hDirection -= 2 * PI;
		}
	}
}

void Camera::move(const Vector2f& moveVec)
{
	position += moveVec;
}

const Vector2f& Camera::getPosition() const
{
	return position;
}

float Camera::getHDirection() const
{
	return hDirection;
}

float Camera::getVDirection() const
{
	return vDirection;
}

float Camera::getHeadHeight() const
{
	return headHeight;
}

void Camera::calculateHeadPos(float floorHeight)
{
	headPos = floorHeight + headHeight;
}

float Camera::getHeadPos() const
{
	return headPos;
}

int Camera::getCurrentSector() const
{
	return currentSector;
}

void Camera::setCurrentSector(int sector)
{
	currentSector = sector;
}
