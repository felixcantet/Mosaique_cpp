#pragma once

#include "int2.h"
#include "color.h"

struct Pixel {
private:
	int2 position;
	Color color;
	
public:
	Pixel() {
		position = int2();
		color = Color();
	}

	Pixel(int2 pos, Color col) 
	{
		this->position = pos;
		this->color = col;
	}

	int getR() const{
		return this->color.r;
	}

	int getG() const {
		return this->color.g;
	}

	int getB() const {
		return this->color.b;
	}

	Color getColor() const {
		return this->color;
	}

	void setColor(Color newColor) {
		this->color = newColor;
	}

	void setR(int r) {
		this->color.r = r;
	}

	void setG(int g) {
		this->color.g = g;
	}

	void setB(int b) {
		this->color.b = b;
	}
};