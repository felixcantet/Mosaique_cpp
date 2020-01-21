#include "Pixel.h"

Pixel::Pixel() {
	this->position = new int2(0, 0);
	this->color = new Color(0, 0, 0);
}

Pixel::Pixel(int2& pos, Color& col)
{
	this->position = new int2(pos);
	this->color = new Color(col);
}

Pixel::Pixel(Pixel& p)
{
	this->position = p.position;
	this->color = p.color;
}

Pixel& Pixel::operator=(Pixel p)
{
	Pixel::swap(p);
	return *this;
}

void Pixel::swap(Pixel& p)
{
	this->position = p.position;
	this->color = p.color;
}

int Pixel::getR() const
{
	return this->color->r;
}

int Pixel::getG() const
{
	return this->color->g;
}

int Pixel::getB() const
{
	return this->color->b;
}

Color Pixel::getColor() const
{
	return *color;
}

void Pixel::setColor(Color& newColor) {
	this->color = &newColor;
}

void Pixel::setR(int r) {
	this->color->r = r;
}

void Pixel::setG(int g) {
	this->color->g = g;
}

void Pixel::setB(int b) {
	this->color->b = b;
}