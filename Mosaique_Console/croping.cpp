#include "croping.h"

Image *crop(const Image &im, int w, int h)
{
	Image* newIm = new Image(w, h);

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			newIm->pixels[i][j] = im.pixels[i][j];
		}
	}

	return newIm;
}

Image* cropCenter(const Image& im, int w, int h)
{
	Image* newIm = new Image(w, h);

	int centerX = im.getWidth() / 2;
	int centerY = im.getHeight() / 2;

	centerX -= w / 2;
	centerY -= h / 2;
	
	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			newIm->pixels[i][j] = im.pixels[i + centerX][j + centerY];
		}
	}

	return newIm;
}

Image* cropRegion(const Image& im, int top, int bot, int left, int right)
{
	Image* newIm = new Image(right-left, bot-top);

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			newIm->pixels[i][j] = im.pixels[i][j];
		}
	}

	return newIm;
}

Image* resize(const Image& im, int w, int h)
{
	Image* newIm = new Image(w, h);

	float coefX = (float)im.getWidth() / (float)newIm->getWidth();
	float coefY = (float)im.getHeight() / (float)newIm->getHeight();

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			int x = i * coefX;
			int y = j * coefY;
			newIm->pixels[i][j] = im.pixels[x][y];
		}
	}

	return newIm;
}
