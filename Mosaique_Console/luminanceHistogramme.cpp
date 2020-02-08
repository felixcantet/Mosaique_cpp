#include "luminance_histogramme.h"
#include <iostream>

luminanceHistogramme::luminanceHistogramme()
{
	for(int i = 0; i < 16; i++)
	{
		this->histogramme[i] = 0;
	}
}

int luminance(Color& color)
{
	int value = (int)(color.r * 0.3) + (int)(color.g * 0.59) + (int)(color.b * 0.11);
	return value;
}

luminanceHistogramme::luminanceHistogramme(const Image& im)
{
	for(int i = 0; i < im.getWidth(); i++)
	{
		for(int j = 0; j < im.getHeight(); j++)
		{
			Color color = im.getPixel(i, j).getColor();
			int lum = luminance(color);
			this->histogramme[int(lum / 16)]++;
		}
	}
}

luminanceHistogramme luminanceHistogramme::operator=(luminanceHistogramme histo)
{
	luminanceHistogramme::swap(histo);
	return *this;
}

void luminanceHistogramme::swap(luminanceHistogramme& histo)
{
	std::swap(this->histogramme, histo.histogramme);
}

unsigned int luminanceHistogramme::getHistoValue(int index) const
{
	return (unsigned int)histogramme[index];
}