#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

Image::Image(const char* imagePath)
{
	// imagepath = path to image
	// width = width of the image
	// height = height of the image
	// channelsNumbers = byte per pixel
	// STBI_RGB = load image format. RGB here
	unsigned char* data = stbi_load(imagePath, &this->width, &this->height, &this->channelsNumbers, STBI_rgb);

	if (data == nullptr)
		std::cout << "Image not load" << std::endl;

	this->pixels = new Pixel * *[width];

	for (int i = 0; i < this->width; i++)
	{
		this->pixels[i] = new Pixel * [height];
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			unsigned char* pixelOffset = data + (i + height * j) * channelsNumbers;
			Color color = Color(pixelOffset[0], pixelOffset[1], pixelOffset[2]);
			Pixel* p = new Pixel(color);
			pixels[i][j] = p;
		}
	}
	
	stbi_image_free(data);
}

Image::Image(int w, int h)
{
	this->width = w;
	this->height = h;
	this->channelsNumbers = 3;

	this->pixels = new Pixel * *[width];

	for (int i = 0; i < this->width; i++)
	{
		this->pixels[i] = new Pixel * [height];
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			pixels[i][j] = new Pixel();
		}
	}
}

Image::Image(const Image& im)
{
	this->height = im.getHeight();
	this->width = im.getWidth();
	this->channelsNumbers = im.channelsNumbers;

	this->pixels = new Pixel * *[this->width];

	for (int i = 0; i < this->width; i++)
	{
		this->pixels[i] = new Pixel * [this->height];
	}

	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Pixel* p = new Pixel(*im.pixels[i][j]);
			this->pixels[i][j] = p;
		}
	}
	
}

Image& Image::operator=(Image im)
{
	Image::swap(im);
	return *this;
}

void Image::swap(Image& im)
{
	std::swap(this->height, im.height);
	std::swap(this->width, im.width);
	std::swap(this->channelsNumbers, im.channelsNumbers);
	std::swap(this->pixels, im.pixels);
}

int Image::getWidth() const
{
	return this->width;
}

int Image::getHeight() const
{
	return this->height;
}

Pixel Image::getPixel(int x, int y) const
{
	return *pixels[x][y];
}

void Image::modifyPixelsRegion(const Image& to, int top, int bot, int left, int right)
{
	for (int i = 0; i < to.getWidth(); i++)
	{
		for (int j = 0; j < to.getHeight(); j++)
		{
			this->pixels[i + left][j + top] = to.pixels[i][j];
		}
	}
}

void Image::writeBackPixels(const char* imgName)
{
	const int size = this->width * this->height * this->channelsNumbers;
	unsigned char* data = new unsigned char[size];
	int index = 0;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[index++] = pixels[j][i]->getR();
			data[index++] = pixels[j][i]->getG();
			data[index++] = pixels[j][i]->getB();
		}
	}
	
	stbi_write_jpg(imgName, this->width, this->height, this->channelsNumbers, data, this->width * this->channelsNumbers);
	stbi_image_free(data);
}