#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include "Pixel.h"
#include "std_image.h"

class Image {

private:
	int width;
	int height;
	int channelsNumbers;
	unsigned char* data;
	

public:
	Pixel*** pixels;

	Image(const char* imagePath);
	Image(int w, int h);
	Image(const Image& im);

	Image& operator=(Image im);
	void swap(Image& im);
	
	~Image()
	{
		// Unload the image at destruction
		stbi_image_free(data);
	}

	int getWidth() const;
	int getHeight() const;
	Pixel getPixel(int x, int y) const;

	void modifyPixelsRegion(const Image& to, int top, int bot, int left, int right);
	
	void writeBackPixels(const char* imgName);

};

#endif