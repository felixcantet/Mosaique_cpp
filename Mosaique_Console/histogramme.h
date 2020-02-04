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

	~Histogramme() {
		delete[] redHistogramme;
		delete[] blueHistogramme;
		delete[] greenHistogramme;
		delete[] luminanceHistogramme;
	}

	void computeHistogrammes(const Image& image);

	unsigned int* getRedHisto() const;
	unsigned int* getGreenHisto() const;
	unsigned int* getBlueHisto() const;
	unsigned int* getluminanceHisto() const;
};