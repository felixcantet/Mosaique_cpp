#include "histogramme.h"
#include "color.h"
#include "traitement.h"
#include <iostream>

Histogramme::Histogramme()
{
	
}

Histogramme::Histogramme(const Image& im)
{
	computeHistogrammes(im);
}

Histogramme::Histogramme(const Histogramme& histo)
{
	for(int i = 0; i < 16; i++)
	{
		this->greenHistogramme[i] = histo.greenHistogramme[i];
	}

	for (int i = 0; i < 16; i++)
	{
		this->redHistogramme[i] = histo.redHistogramme[i];
	}

	for (int i = 0; i < 16; i++)
	{
		this->blueHistogramme[i] = histo.blueHistogramme[i];
	}

	for (int i = 0; i < 16; i++)
	{
		this->luminanceHistogramme[i] = histo.luminanceHistogramme[i];
	}
}


Histogramme Histogramme::operator=(Histogramme histo)
{
	Histogramme::swap(histo);
	return *this;
}

void Histogramme::swap(Histogramme& histo)
{
	std::swap(this->blueHistogramme, histo.blueHistogramme);
	std::swap(this->redHistogramme, histo.redHistogramme);
	std::swap(this->greenHistogramme, histo.greenHistogramme);
	std::swap(this->luminanceHistogramme, histo.luminanceHistogramme);
}

void Histogramme::computeHistogrammes(const Image& image)
{
	Image lum(luminance(image));
	for (int i = 0; i < image.getWidth(); i++) 
	{
		for (int j = 0; j < image.getHeight(); j++) 
		{
			Color color = image.getPixel(i, j).getColor();
			redHistogramme[color.r/16] += 1;
			blueHistogramme[color.b/16] += 1;
			greenHistogramme[color.g/16] += 1;
			luminanceHistogramme[lum.pixels[i][j]->getR() / 16];
		}
	}
}

unsigned int* Histogramme::getBlueHisto() const
{
	return (unsigned int*)blueHistogramme;
}

unsigned int* Histogramme::getGreenHisto() const
{
	return (unsigned int*)greenHistogramme;
}

unsigned int* Histogramme::getRedHisto() const
{
	return (unsigned int*)redHistogramme;
}

unsigned int* Histogramme::getluminanceHisto() const
{
	return (unsigned int*)luminanceHistogramme;
}
