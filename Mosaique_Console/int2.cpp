#include "int2.h"
#include <iostream>

int2::int2()
{
	this->x = 0;
	this->y = 0;
}

int2::int2(int x, int y)
{
	this->x = x;
	this->y = y;
}

int2::int2(int2& cop)
{
	this->x = cop.x;
	this->y = cop.y;
}

int2& int2::operator=(int2 cop)
{
	int2::swap(cop);
	return *this;
}

void int2::swap(int2& cop)
{
	std::swap(x, cop.x);
	std::swap(y, cop.y);
}