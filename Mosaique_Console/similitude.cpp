#include "Image.h"
#include "histogramme.h"
#include <iostream>
#include "luminance_histogramme.h"
#include "utils.h"

int diffVal(const Image& im1, const Image& im2)
{
	int finalDiff = 0;
	for (int i = 0; i < im1.getWidth(); i++)
	{
		for (int j = 0; j < im1.getHeight(); j++)
		{
			unsigned char rDiff = abs(im1.pixels[i][j].getR() - im2.pixels[i][j].getR());
			unsigned char gDiff = abs(im1.pixels[i][j].getG() - im2.pixels[i][j].getG());
			unsigned char bDiff = abs(im1.pixels[i][j].getB() - im2.pixels[i][j].getB());

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

int diffLuminanceHisto(const Image& im1, const Image& im2)
{
	luminanceHistogramme histo1(im1);
	luminanceHistogramme histo2(im2);
	int diff = 0;
	for(int i = 0; i < 16; i++)
	{
		// Comparaison pour chaque entrée de l'histogramme
		diff += abs((int)histo1.getHistoValue(i) - (int)histo2.getHistoValue(i));
	}

	return int(diff / 16);
}

// Calcul la moyenne des différences HSV pour chaque pixel
int diffHSV(const Image& im1, const Image& im2, float weightH, float weightS, float weightV)
{
	int diff = 0;

	// Conversion des couleurs de chaque pixel des deux image en hsv et comparaison
	for (int i = 0; i < im1.getWidth(); i++)
	{
		for (int j = 0; j < im1.getHeight(); j++)
		{
			
			Color hsvImage1 = rgbToHsv(im1.getPixel(i, j).getColor());
			Color hsvImage2 = rgbToHsv(im2.getPixel(i, j).getColor());

			unsigned char diffH = abs(hsvImage1.r - hsvImage2.r);
			unsigned char diffS = abs(hsvImage1.g - hsvImage2.g);
			unsigned char diffV = abs(hsvImage1.b - hsvImage2.b);

			diff += (diffH * weightH + diffS * weightS + diffV * weightV) / 3;
		}
	}

	return diff / (im1.getWidth() * im1.getHeight());
}