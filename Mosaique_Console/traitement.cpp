#include "traitement.h"

#include "Image.h"

Image* blanckWhite(Image& im)
{
	Image* newIm = &im;

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			float value = (newIm->pixels[i][j]->getR() + newIm->pixels[i][j]->getG() + newIm->pixels[i][j]->getB()) / 3;
			newIm->pixels[i][j] = new Pixel(*(new Color((int)value, (int)value, (int)value)));
		}
	}

	return newIm;
}

Image* blackOrWhite(Image& im)
{
	Image* newIm = blanckWhite(im);

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			newIm->pixels[i][j] = newIm->pixels[i][j]->getR() >= 128 ? new Pixel(*new Color(255, 255, 255)) : new Pixel(*new Color(0, 0, 0));
		}
	}
	
	return newIm;
}