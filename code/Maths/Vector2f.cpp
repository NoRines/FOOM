#include "Vector2f.h"
#include <cmath>

Vector2f::Vector2f() :
x(0.0f),
y(0.0f)
{
}

Vector2f::Vector2f(float x, float y) :
x(x),
y(y)
{
}

float Vector2f::length() const
{
	return sqrt(x*x + y*y);
}

float Vector2f::dot(const Vector2f& vec) const
{
	return (x * vec.x) + (y * vec.y);
}

void Vector2f::normalize()
{
	float l = length();
	if(l > 0.001f)
	{
		*this /= l;
	}
}

Vector2f Vector2f::getUnit() const
{
	float l = length();
	if(l > 0.001f)
	{
		Vector2f unit = *this / length();
		return unit;
	}
	return *this;
}

const Vector2f& Vector2f::rotate(float amount)
{
	float newX = x * cos(amount) - y * sin(amount);
	float newY = x * sin(amount) + y * cos(amount);
	x = newX;
	y = newY;
	return *this;
}

Vector2f Vector2f::operator+(const Vector2f& v) const
{
	return Vector2f(
		x + v.x,
		y + v.y);
}

Vector2f Vector2f::operator-(const Vector2f& v) const
{
	return Vector2f(
		x - v.x,
		y - v.y);
}

Vector2f Vector2f::operator*(float s) const
{
	return Vector2f(
		x * s,
		y * s);
}

Vector2f Vector2f::operator/(float s) const
{
	return Vector2f(
		x / s,
		y / s);
}

Vector2f& Vector2f::operator+=(const Vector2f& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2f& Vector2f::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2f& Vector2f::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

