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
	Histogramme(const Image* image) {
		redHistogramme = new unsigned int[255];
		redHistogramme = new unsigned int[255];
		redHistogramme = new unsigned int[255];
		luminanceHistogramme = new unsigned int[255];
	}

	~Histogramme() {
		delete[] redHistogramme;
		delete[] blueHistogramme;
		delete[] greenHistogramme;
		delete[] luminanceHistogramme;
	}
	
	int getLuminance(Color* color) {
		return (int)(color->r * 0.2126 + color->g * 0.7152 + color->b * 0.0722);
	}

	unsigned int* computeHistogrammes(const Image* image) 
	{
		for (int i = 0; i < image->getWidth(); i++) {
			for (int j = 0; j < image->getHeight(); j++) {
				Color color = image->getPixel(i, j).getColor();
				redHistogramme[color.r] += 1;
				blueHistogramme[color.b] += 1;
				greenHistogramme[color.g] += 1;
				luminanceHistogramme[getLuminance(&color)] += 1;

			}
		}
	}

};