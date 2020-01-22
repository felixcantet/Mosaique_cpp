#include "traitement.h"

Image *crop(Image &im, int w, int h)
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

Image* cropCenter(Image& im, int w, int h)
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

Image* cropRegion(Image& im, int top, int bot, int left, int right)
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