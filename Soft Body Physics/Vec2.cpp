#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {}


Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin) {}


bool Vec2::operator==(const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}


bool Vec2::operator!=(const Vec2& rhs) const
{
	return (x != rhs.x || y != rhs.y);
}


Vec2 Vec2::operator+(const Vec2& rhs) const
{

	return Vec2(x + rhs.x, y + rhs.y);
}


Vec2 Vec2::operator-(const Vec2& rhs) const
{

	return Vec2(x - rhs.x, y - rhs.y);
}


Vec2 Vec2::operator*(const float val) const
{
	return Vec2(val * x, val * y);
}


Vec2 Vec2::operator/(const float val) const
{

	return Vec2(x / val, y / val);
}


void Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}


void Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}


void Vec2::operator*=(const float val)
{
	x *= val;
	y *= val;
}


void Vec2::operator/=(const float val)
{
	x /= val;
	y /= val;
}


float Vec2::dist(const Vec2& rhs) const
{
	float distance = sqrt(rhs.x * x + rhs.y * y);
	return distance;
}


float Vec2::length() const
{
	float length = sqrt(x * x + y * y);
	return length;
}

void Vec2::normalize() {
	float length = sqrt(x * x + y * y);
	if (length != 0) {
		x /= length;
		y /= length;
	}
}
