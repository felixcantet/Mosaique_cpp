#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_

#include "int2.h"
#include "color.h"

struct Pixel {
private:
	int2* position;
	Color* color;
	
public:
	~Pixel() {};
	
	Pixel();
	Pixel(int2& pos, Color& col);
	Pixel(Pixel& p);

	Pixel& operator=(Pixel p);
	void swap(Pixel& p);
	
	int getR() const;
	int getG() const;
	int getB() const;
	Color getColor() const;

	void setColor(Color& newColor);
	void setR(int r);
	void setG(int g);
	void setB(int b);
};

#endif