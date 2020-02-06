#include "Pixel.h"

Pixel::Pixel()
{
	this->color = Color(0, 0, 0);
}

Pixel::Pixel(const Color& col)
{
	this->color = Color(col);
}

Pixel::Pixel(const Pixel& p)
{
	this->color = p.color;
}

Pixel& Pixel::operator=(Pixel p)
{
	Pixel::swap(p);
	return *this;
}

void Pixel::swap(Pixel& p)
{
	this->color = p.color;
}

unsigned char Pixel::getR() const
{
	return this->color.r;
}

unsigned char Pixel::getG() const
{
	return this->color.g;
}

unsigned char Pixel::getB() const
{
	return this->color.b;
}

Color Pixel::getColor() const
{
	return color;
}

void Pixel::setColor(const Color& newColor) {
	this->color = newColor;
}

void Pixel::setR(unsigned char r) {
	this->color.r = r;
}

void Pixel::setG(unsigned char g) {
	this->color.g = g;
}

void Pixel::setB(unsigned char b) {
	this->color.b = b;
}