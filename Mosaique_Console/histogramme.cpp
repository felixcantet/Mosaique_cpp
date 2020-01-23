#include "histogramme.h"
#include "color.h"


Histogramme::Histogramme(const Image* image) {
	this->redHistogramme = new unsigned int[255];
	this->greenHistogramme = new unsigned int[255];
	this->blueHistogramme = new unsigned int[255];
	this->luminanceHistogramme = new unsigned int[255];
}


int Histogramme::getLuminance(Color* color) {

	float r = color->r / 255;
	float g = color->g / 255;
	float b = color->b / 255;
	int lum = (int)((r * 0.2126 + g * 0.7152 + b * 0.0722) * 255);

	return lum;
}

void Histogramme::computeHistogrammes(const Image* image) {
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
