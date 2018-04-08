#include "MiniginPCH.h"
#include "Structs.h"


Float2 operator+(const Float2 lhs, const Float2 rhs)
{
	return Float2(lhs.x + rhs.x, lhs.y + rhs.y);
}
Float2 operator-(const Float2 lhs, const Float2 rhs)
{
	return Float2(lhs.x - rhs.x, lhs.y - rhs.y);
}
Float2 operator*(const Float2 lhs, const Float2 rhs)
{
	return Float2(lhs.x * rhs.x, lhs.y * rhs.y);
}
Float2 operator*(const float lhs, const Float2 rhs)
{
	return Float2(lhs * rhs.x, lhs* rhs.y);
}
Float2 operator*(const Float2 lhs, const float rhs)
{
	return Float2(lhs.x * rhs, lhs.y * rhs);
}

Float3 operator+(const Float3 lhs, const Float3 rhs)
{
	return Float3(lhs.x + rhs.x, lhs.y + lhs.y, lhs.z + lhs.z);
}
Float3 operator-(const Float3 lhs, const Float3 rhs)
{
	return Float3(lhs.x - rhs.x, lhs.y - lhs.y, lhs.z - lhs.z);
}
Float3 operator*(const Float3 lhs, const Float3 rhs)
{
	return Float3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}
Float3 operator*(const float lhs, const Float3 rhs)
{
	return Float3(lhs * rhs.x, lhs* rhs.y, lhs * rhs.z);
}
Float3 operator*(const Float3 lhs, const float rhs)
{
	return Float3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}