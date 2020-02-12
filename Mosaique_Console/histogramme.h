#pragma once
#include "Image.h"

class Histogramme
{
private:
	unsigned int redHistogramme[16];
	unsigned int greenHistogramme[16];
	unsigned int blueHistogramme[16];
	unsigned int luminanceHistogramme[16];

public:
	Histogramme();
	Histogramme(const Image& im);
	Histogramme(const Histogramme& histo);

	Histogramme operator=(Histogramme histo);
	void swap(Histogramme& histo);

	~Histogramme() {}

	void computeHistogrammes(const Image& image);

	unsigned int getRedHistoValue(int i) const;
	unsigned int getGreenHistoValue(int i) const;
	unsigned int getBlueHistoValue(int i) const;
	unsigned int getluminanceHistoValue(int i) const;
};