#pragma once

//============
//Float2
//============

struct Float2
{
	Float2() = default;
	Float2(float X, float Y) :x{X}, y{Y}{}
	void operator++()
	{
		++x;
		++y;
	}
	void operator--()
	{
		--x;
		--y;
	}

	float x, y;
};

Float2 operator+(const Float2 lhs, const Float2 rhs);
Float2 operator-(const Float2 lhs, const Float2 rhs);
Float2 operator*(const Float2 lhs, const Float2 rhs);
Float2 operator*(const float lhs, const Float2 rhs);
Float2 operator*(const Float2 lhs, const float rhs);

//==============
//Float3
//==============
struct Float3
{
	Float3() = default;
	Float3(float X, float Y, float Z)
		:x{X}, y{Y}, z{Z}{}

	void operator++()
	{
		++x;
		++y;
		++z;
	}
	void operator--()
	{
		--x;
		--y;
		--z;
	}

	float x, y, z;
};

Float3 operator+(const Float3 lhs, const Float3 rhs);
Float3 operator-(const Float3 lhs, const Float3 rhs);
Float3 operator*(const Float3 lhs, const Float3 rhs);
Float3 operator*(const float lhs, const Float3 rhs);
Float3 operator*(const Float3 lhs, const float rhs);
