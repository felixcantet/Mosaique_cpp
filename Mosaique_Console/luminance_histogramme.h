#pragma once
#include "Image.h"

class luminanceHistogramme
{
private:
	unsigned int histogramme[16];

public:
	luminanceHistogramme();
	luminanceHistogramme(const Image& im);

	luminanceHistogramme operator=(luminanceHistogramme histo);
	void swap(luminanceHistogramme& histo);
	unsigned int getHistoValue(int index) const;


};