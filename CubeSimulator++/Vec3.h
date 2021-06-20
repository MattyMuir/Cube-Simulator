#pragma once
struct Vec3
{
	int x, y, z;

	Vec3()
		:x(0), y(0), z(0) {};
	Vec3(int x_, int y_, int z_)
		:x(x_), y(y_), z(x_) {};
};