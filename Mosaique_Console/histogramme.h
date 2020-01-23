#pragma once
#include "Image.h"
#include "color.h"


class Histogramme {
private:
	unsigned int* redHistogramme;
	unsigned int* greenHistogramme;
	unsigned int* blueHistogramme;
	unsigned int* luminanceHistogramme;

public:
	Histogramme(const Image* image);

	~Histogramme() {
		delete[] redHistogramme;
		delete[] blueHistogramme;
		delete[] greenHistogramme;
		delete[] luminanceHistogramme;
	}
	
	int getLuminance(Color* color);

	void computeHistogrammes(const Image* image);

};