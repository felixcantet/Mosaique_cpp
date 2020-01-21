#ifndef _IMAGE_HPP
#define _IMAGE_HPP


#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <string>

#include "Pixel.h"
class Image {

private:
	int width;
	int height;
	int channelsNumbers;
	unsigned char* data;
	

public:
	Pixel** pixelAcces;

	Image(const char* imagePath)
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
		this->pixelAcces = new Pixel * [width];
		for (int i = 0; i < this->width; i++) {
			this->pixelAcces[i] = new Pixel[height];
		}
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				unsigned char* pixelOffset = data + (i + height * j) * channelsNumbers;
				auto color = Color(pixelOffset[0], pixelOffset[1], pixelOffset[2]);
				pixelAcces[i][j] = Pixel(int2(i, j), color);
			}
		}
	}

	Image(int w, int h) {
		this->width = w;
		this->height = h;
		this->channelsNumbers = 3;
		this->data = new unsigned char[width * height * channelsNumbers];
		pixelAcces = new Pixel * [width];
		for (int i = 0; i < width; i++) {
			this->pixelAcces[i] = new Pixel[height];
		}

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				pixelAcces[i][j] = Pixel();
			}
		}
	}

	~Image() {
		// Unload the image at destruction
		stbi_image_free(data);
	}

	int getWidth() const {
		return this->width;
	}

	int getHeight() const {
		return this->height;
	}

	Pixel getPixel(int x, int y) const {
		return pixelAcces[x][y];
	}

	void writeBackPixels()
	{
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				data[(i + height * j) * channelsNumbers] = pixelAcces[i][j].getR();
				data[(i + height * j) * channelsNumbers + 1] = pixelAcces[i][j].getG();
				data[(i + height * j) * channelsNumbers + 2] = pixelAcces[i][j].getB();
			}
		}

		stbi_write_jpg("Custom.jpg", this->width, this->height, this->channelsNumbers, (void*)data, this->width * this->channelsNumbers);
	}

};

#endif