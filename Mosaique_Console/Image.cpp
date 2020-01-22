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
	data = stbi_load(imagePath, &this->width, &this->height, &this->channelsNumbers, STBI_rgb);

	if (data == nullptr)
		std::cout << "Image not load" << std::endl;

	std::cout << "ChannelNumbers : " << channelsNumbers << std::endl;

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
			Color* color = new Color(pixelOffset[0], pixelOffset[1], pixelOffset[2]);
			Pixel* p = new Pixel(*color);
			pixels[i][j] = p;
		}
	}
}

Image::Image(int w, int h)
{
	this->width = w;
	this->height = h;
	this->channelsNumbers = 3;

	this->data = new unsigned char[width * height * channelsNumbers];
	
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

Image::Image(Image& im)
{
	this->height = im.getHeight();
	this->width = im.getWidth();
	this->channelsNumbers = im.channelsNumbers;

	int dataSize = this->width * this->height * this->channelsNumbers;
	this->data = new unsigned char[dataSize];

	for(int i = 0; i < dataSize; i++)
	{
		char a = im.data[i];
		this->data[i] = a;
	}

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
	std::swap(this->data, im.data);
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

void Image::writeBackPixels(const char* imgName)
{
	//for (int i = 0; i < width; i++)
	//{
	//	for (int j = 0; j < height; j++)
	//	{
	//		data[(i + height * j) * channelsNumbers] = pixels[i][j]->getR();
	//		data[(i + height * j) * channelsNumbers + 1] = pixels[i][j]->getG();
	//		data[(i + height * j) * channelsNumbers + 2] = pixels[i][j]->getB();
	//	}
	//}

	int index = 0;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[index++] = (unsigned char)pixels[j][i]->getR();
			data[index++] = (unsigned char)pixels[j][i]->getG();
			data[index++] = (unsigned char)pixels[j][i]->getB();
		}
	}
	
	stbi_write_jpg(imgName, this->width, this->height, this->channelsNumbers, (void*)data, this->width * this->channelsNumbers);
}