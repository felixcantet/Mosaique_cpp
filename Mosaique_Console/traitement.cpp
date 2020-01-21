#include "traitement.h"

Image *crop(Image *im, int w, int h)
{
	Image* newIm = new Image(w, h);

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			newIm->pixels[i][j] = im->pixels[i][j];
		}
	}

	return newIm;
}