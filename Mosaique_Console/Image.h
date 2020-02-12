#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include "Pixel.h"
#include "std_image.h"

class Image {

private:
	int width;
	int height;
	int channelsNumbers;
	

public:
	Pixel** pixels;

	Image(const char* imagePath);
	Image(int w, int h);
	Image(const Image& im);

	Image& operator=(Image im);
	void swap(Image& im);
	
	~Image()
	{
		for (int i = 0; i < this->width; i++)
		{
			delete[] this->pixels[i];
		}
		
		delete[] pixels;
	}

	int getWidth() const;
	int getHeight() const;
	Pixel getPixel(int x, int y) const;

	void modifyPixelsRegion(const Image& to, int top, int bot, int left, int right);
	
	void writeBackPixels(const char* imgName);

};

#endif