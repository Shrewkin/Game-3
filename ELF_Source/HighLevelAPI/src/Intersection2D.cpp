//==================================================================-
/*
/file   Intersection2D.cpp
/author Jakob McFarland
/date   11/15/2018
/brief

This is the implementation file for all member functions
of the class Intersection2D, as specified in specification
file Intersection2D.h.

*/
//==================================================================-

#include "stdafx.h"
#include "Intersection2D.h"

//------------------------------------------------------------------------------
// Public Function Declarations:
//------------------------------------------------------------------------------

// Check whether a point and circle intersect.
// Params:
//  point = The point in the intersection.
//  circle = The circle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointCircleIntersection(const Vector2D& point, const Circle& circle)
{
	if (point.DistanceSquared(circle.center) <= circle.radius * circle.radius)
	{
		return true;
	}

	return false;
}

// Check whether a point and rectangle intersect.
// Params:
//  point = The point in the intersection.
//  rect  = The rectangle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointRectangleIntersection(const Vector2D& point, const BoundingRectangle& rect)
{
	if (point.x < rect.left) return false;
	if (point.x > rect.right) return false;
	if (point.y < rect.bottom) return false;
	if (point.y > rect.top) return false;
	return true;
}

// Check whether two circles intersect.
// Params:
//  circle1 = The first circle.
//  circle2 = The second circle.
// Returns:
//   True if intersection, false otherwise.
bool CircleCircleIntersection(const Circle& circle1, const Circle& circle2)
{
	if (circle1.center.DistanceSquared(circle2.center) <= 
		circle1.radius + circle2.radius * circle1.radius + circle2.radius)
	{
		return true;
	}

	return false;
}

// Check whether two rectangles intersect.
// Params:
//  rect1 = The first rectangle.
//	rect2 = The second rectangle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleRectangleIntersection(const BoundingRectangle& rect1, const BoundingRectangle& rect2)
{
	if (rect1.right < rect2.left) return false;
	if (rect1.left > rect2.right) return false;
	if (rect1.top < rect2.bottom) return false;
	if (rect1.bottom > rect2.top) return false;
	return true;
}

// Check whether a rectangle and circle intersect.
// Params:
//  rect = The rectangle.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleCircleIntersection(const BoundingRectangle& rect, const Circle& circle)
{
	Vector2D point;

	point.x = clamp(circle.center.x, rect.left, rect.right);
	point.y = clamp(circle.center.y, rect.bottom, rect.top);

	if (point.DistanceSquared(circle.center) <= circle.radius * circle.radius)
	{
		return true;
	}

	return false;
}

// Check whether a rectangle and circle intersect.
// Params:
//  val = value to be clamped.
//  min  = minimum value after clamp.
//  max  = maximum value after clamp.
// Returns:
//   clamped value.
float clamp(float val, float min, float max)
{
	if (val > max) val = max;
	else if (val < min) val = min;
	return val;
}

//------------------------------------------------------------------------------
