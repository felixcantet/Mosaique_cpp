#include "Image.h"

int diffVal(const Image& im1, const Image& im2)
{
	int finalDiff = 0;
	for (int i = 0; i < im1.getWidth(); i++)
	{
		for (int j = 0; j < im1.getHeight(); j++)
		{
			int rDiff = abs(im1.pixels[i][j]->getR() - im2.pixels[i][j]->getR());
			int gDiff = abs(im1.pixels[i][j]->getG() - im2.pixels[i][j]->getG());
			int bDiff = abs(im1.pixels[i][j]->getB() - im2.pixels[i][j]->getB());

			finalDiff += (rDiff + gDiff + bDiff) / 3;
		}
	}

	return finalDiff/(im1.getWidth() * im1.getHeight());
}
