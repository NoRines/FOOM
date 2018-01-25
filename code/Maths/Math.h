#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "Vector2f.h"

#define PI 3.14159265359

float distFromLine(const Vector2f& point, const Vector2f& linePoint, const Vector2f& lineNormal);
bool isPointProjectedOnLineSegment(const Vector2f& point, const Vector2f& line1, const Vector2f& line2, Vector2f& resultPoint);
bool lineSegmentIntersection(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, Vector2f& res);
bool lineIntersection(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, Vector2f& res);

#endif
