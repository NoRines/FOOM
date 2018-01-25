#ifndef VECTOR2F_H
#define VECTOR2F_H

struct Vector2f
{
	float x,y;

	Vector2f();
	Vector2f(float x, float y);


	float length() const;
	float dot(const Vector2f& vec) const;

	void normalize();
	Vector2f getUnit() const;

	const Vector2f& rotate(float amount);

	Vector2f operator+(const Vector2f& v) const;
	Vector2f operator-(const Vector2f& v) const;
	Vector2f operator*(float s) const;
	Vector2f operator/(float s) const;

	Vector2f& operator+=(const Vector2f& v);
	Vector2f& operator-=(const Vector2f& v);
	Vector2f& operator*=(float s);
	Vector2f& operator/=(float s);
};

#endif
