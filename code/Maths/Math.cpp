#include "Math.h"

float distFromLine(const Vector2f& point, const Vector2f& linePoint, const Vector2f& lineNormal)
{
	return (point - linePoint).dot(lineNormal.getUnit());
}

bool isPointProjectedOnLineSegment(const Vector2f& point, const Vector2f& line1, const Vector2f& line2, Vector2f& resultPoint)
{
	float slope = (line2.y - line1.y) / (line2.x - line1.x);
	float offset = line1.y + (slope * line1.x);

	resultPoint.x = (slope * point.y + point.x - slope * offset) / (slope * slope + 1.0f);
	resultPoint.y = (slope * slope * point.y + slope * point.x + offset) / (slope * slope + 1.0f);

	float lineLength = (line2 - line1).length();
	float distToPoint1 = (resultPoint - line1).length();
	float distToPoint2 = (line2 - resultPoint).length();

	if(distToPoint1 < lineLength && distToPoint2 < lineLength)
	{
		return true;
	}
	return false;
}

bool lineSegmentIntersection(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, Vector2f& res)
{
	float A1 = p1.y - p0.y;
	float B1 = p0.x - p1.x;
	float C1 = A1*p0.x + B1*p0.y;

	float A2 = p3.y - p2.y;
	float B2 = p2.x - p3.x;
	float C2 = A2*p2.x + B2*p2.y;

	float denominator = A1*B2 - A2*B1;

	if(denominator > 0.001f && denominator < -0.001f)
	{
		return false;
	}

	float intersectX = (B2*C1 - B1*C2) / denominator;
	float intersectY = (A1*C2 - A2*C1) / denominator;

	float rx0 = -5.0f; // some negative default value
	float ry0 = -5.0f;
	if((p1.x - p0.x) > 0.001f || (p1.x - p0.x) < -0.001f)
	{
		rx0 = (intersectX - p0.x) / (p1.x - p0.x);
	}
	if((p1.y - p0.y) > 0.001f || (p1.y - p0.y) < -0.001f)
	{
		ry0 = (intersectY - p0.y) / (p1.y - p0.y);
	}

	float rx1 = -5.0f; // some negative default value
	float ry1 = -5.0f;
	if((p3.x - p2.x) > 0.001f || (p3.x - p2.x) < -0.001f)
	{
		rx1 = (intersectX - p2.x) / (p3.x - p2.x);
	}
	if((p3.y - p2.y) > 0.001f || (p3.y - p2.y) < -0.001f)
	{
		ry1 = (intersectY - p2.y) / (p3.y - p2.y);
	}


	if(((rx0 >= 0.0f && rx0 <= 1.0f) ||
		(ry0 >= 0.0f && ry0 <= 1.0f)) &&
		((rx1 >= 0.0f && rx1 <= 1.0f) ||
		(ry1 >= 0.0f && ry1 <= 1.0f)))
	{
		res.x = intersectX;
		res.y = intersectY;
		return true;
	}
	return false;
}

bool lineIntersection(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, Vector2f& res)
{
	float A1 = p1.y - p0.y;
	float B1 = p0.x - p1.x;
	float C1 = A1*p0.x + B1*p0.y;

	float A2 = p3.y - p2.y;
	float B2 = p2.x - p3.x;
	float C2 = A2*p2.x + B2*p2.y;

	float denominator = A1*B2 - A2*B1;

	if(denominator > 0.001f && denominator < -0.001f)
	{
		return false;
	}

	res.x = (B2*C1 - B1*C2) / denominator;
	res.y = (A1*C2 - A2*C1) / denominator;
	return true;
}
