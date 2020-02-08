#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include "color.h"
#include <iostream>
#include <math.h>
float lerp(float a, float b, float f);

Color rgbToHsv(const Color& rgb)
{
	float r = rgb.r / 255.0f;
	float g = rgb.g / 255.0f;
	float b = rgb.b / 255.0f;

	float cmax = std::fmaxf(r, std::fmaxf(g, b));
	float cmin = std::fminf(r, std::fminf(g, b));

	float diff = cmax - cmin;
	float h = -1.0f;
	float s = -1.0f;
	if (cmax == cmin)
		h = 0.0f;

	// Compute h
	else if(cmax == r)
	{
		h = fmodf((60 * ((g - b) / diff) + 360), 360);
	}
	else if (cmax == g)
	{
		h = fmodf((60 * ((b - r) / diff) + 120), 360);
	}

	else if (cmax == b)
	{
		h = fmodf((60 * ((r - g) / diff) + 240), 360);
	}
	 // compute s
	if (cmax == 0)
		s = 0;

	else
		s = (diff / cmax) * 100;
	
	// compute v
	float v = cmax * 100;

	return Color(h, s, v);

}

#endif
