#include "color.h"
#include <iostream>

Color::Color()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

Color::Color(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color(Color& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
}

Color& Color::operator=(Color c)
{
	Color::swap(c);
	return *this;
}

void Color::swap(Color& c)
{
	std::swap(r, c.r);
	std::swap(g, c.g);
	std::swap(b, c.b);
}