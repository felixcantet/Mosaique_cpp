#pragma once
struct Color {
	int r;
	int g;
	int b;

public:

	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	Color(int r, int g, int b) 
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};