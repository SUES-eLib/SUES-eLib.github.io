#include "pch.h"
#include "CP3.h"
CP3::CP3(void)
{
	x = 0, y = 0, z = 0, w = 1;
}
CP3::CP3(double x, double y, double z) :CP2(x, y)
{
	this->z = z;
}
CP3::~CP3(void)
{
}
CP3 operator + (const CP3& p0, const CP3& p1)
{
	CP3 result;
	result.x = p0.x + p1.x;
	result.y = p0.y + p1.y;
	result.z = p0.z + p1.z;
	return result;
}
CP3 operator -(const CP3& p0, const CP3& p1)
{
	CP3 result;
	result.x = p0.x - p1.x;
	result.y = p0.y - p1.y;
	result.z = p0.z - p1.z;
	return result;
}
CP3 operator *(const CP3& p, double scalar)
{
	return CP3(p.x * scalar, p.y * scalar, p.z * scalar);
}
CP3 operator *(double scalar, const CP3& p)
{
	return CP3(p.x * scalar, p.y * scalar, p.z * scalar);
}
CP3 operator /(const CP3& p, double scalar)
{
	if (fabs(scalar) < 1e-4)
		scalar = 1.0;
	CP3 result;
	result.x = p.x / scalar;
	result.y = p.y / scalar;
	result.z = p.z / scalar;
	return result;
}