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
	
	int getR() const;
	int getG() const;
	int getB() const;
	Color getColor() const;

	void setColor(const Color& newColor);
	void setR(int r);
	void setG(int g);
	void setB(int b);
};

#endif