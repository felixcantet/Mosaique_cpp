#include "Image.h"
#include "histogramme.h"
#include <iostream>

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

int diffHisto(const Image& im1, const Image& im2)
{
	Histogramme histoIm1(im1);
	Histogramme histoIm2(im2);

	int redValues = 0;
	int blueValues = 0;
	int greenValues = 0;
	
	for(int i = 0; i < 16; i++)
	{
		redValues += abs((int)histoIm1.getRedHistoValue(i) - (int)histoIm2.getRedHistoValue(i));
		blueValues += abs((int)histoIm1.getBlueHistoValue(i) - (int)histoIm2.getBlueHistoValue(i));
		greenValues += abs((int)histoIm1.getGreenHistoValue(i) - (int)histoIm2.getGreenHistoValue(i));
	}

	return (redValues + blueValues + greenValues) / 3;
}