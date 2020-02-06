#ifndef _COLOR_HPP
#define _COLOR_HPP

struct Color
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;

	~Color() {};
	
	Color();
	Color(unsigned char r, unsigned char g, unsigned char b);
	Color(const Color& c);

	Color& operator=(Color c);
	void swap(Color& c);
};

#endif