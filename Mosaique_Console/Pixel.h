#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_

#include "color.h"

struct Pixel {
private:
	Color color;
	
public:
	~Pixel() {};
	
	Pixel();
	Pixel(const Color& col);
	Pixel(const Pixel& p);

	Pixel& operator=(Pixel p);
	void swap(Pixel& p);
	
	unsigned char getR() const;
	unsigned char getG() const;
	unsigned char getB() const;
	Color getColor() const;

	void setColor(const Color& newColor);
	void setR(unsigned char r);
	void setG(unsigned char g);
	void setB(unsigned char b);
};

#endif