#ifndef _COLOR_HPP
#define _COLOR_HPP

struct Color
{
public:
	int r;
	int g;
	int b;

	~Color() {};
	
	Color();
	Color(int r, int g, int b);
	Color(Color& c);

	Color& operator=(Color c);
	void swap(Color& c);
};

#endif