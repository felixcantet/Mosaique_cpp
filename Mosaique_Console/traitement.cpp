#include "traitement.h"

#include "Image.h"
#include <vector>

Image luminance(const Image& im)
{
	Image newIm = Image(im);

	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			float r = (float)newIm.pixels[i][j].getR();
			float g = (float)newIm.pixels[i][j].getG();
			float b = (float)newIm.pixels[i][j].getB();

			float value = r * 0.2125f + g * 0.7154f + b * 0.072f;
			value = value > 255 ? 255 : value;

			newIm.pixels[i][j] = Pixel(Color((unsigned char)value, (unsigned char)value, (unsigned char)value));
		}
	}

	return newIm;
}

Image sepia(const Image& im)
{
	Image newIm = Image(im);
	
	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			float r = (float)newIm.pixels[i][j].getR();
			float g = (float)newIm.pixels[i][j].getG();
			float b = (float)newIm.pixels[i][j].getB();

			float newR = r * 0.393f + g * 0.769f + b * 0.189f;
			float newG = r * 0.349f + g * 0.686f + b * 0.168f;
			float newB = r * 0.272f + g * 0.534f + b * 0.131f;

			newR = newR > 255 ? 255 : newR;
			newG = newG > 255 ? 255 : newG;
			newB = newB > 255 ? 255 : newB;
			
			newIm.pixels[i][j] = Pixel(Color((unsigned char)newR, (unsigned char)newG, (unsigned char)newB));
		}
	}

	return newIm;
}

Image blackOrWhite(const Image& im)
{
	Image newIm = Image(im);

	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			float somme = (newIm.pixels[i][j].getR() + newIm.pixels[i][j].getG() + newIm.pixels[i][j].getB()) / 3;
			newIm.pixels[i][j] = somme >= 127.5f ? Pixel(Color(255, 255, 255)) : Pixel(Color(0, 0, 0));
		}
	}
	
	return newIm;
}

Image invertColor(const Image& im)
{
	Image newIm = Image(im);

	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			newIm.pixels[i][j] = Pixel(Color(255 - im.pixels[i][j].getR(), 255 - im.pixels[i][j].getG(), 255 - im.pixels[i][j].getB()));
		}
	}

	return newIm;
}

Image meanshift(const Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold, int iterations)
{
	Image copy = Image(im);
	
	for(int i = 0; i < iterations; i++)
	{
		copy = iterateMeanshift(copy, radius, ‍‍​‌‌﻿﻿​﻿threshold);
	}

	return copy;
}

Image iterateMeanshift(const Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold)
{
	int voisinAdd = 0;
	int rAdd = 0;
	int gAdd = 0;
	int bAdd = 0;

	Image copy = Image(im);

	for(int i = 0; i < copy.getWidth(); i++)
	{
		for(int j = 0; j < copy.getHeight(); j++)
		{
			int minX = i - radius < 0 ? 0 : i - radius;
			int minY = j - radius < 0 ? 0 : j - radius;
			int maxX = i + radius + 1> copy.getWidth() ? copy.getWidth() : i + radius + 1;
			int maxY = j + radius + 1> copy.getHeight() ? copy.getHeight() : j + radius + 1;

			unsigned char rCrt = im.pixels[i][j].getR();
			unsigned char gCrt = im.pixels[i][j].getG();
			unsigned char bCrt = im.pixels[i][j].getB();

			for(int k = minX; k < maxX; k++)
			{
				for (int l = minY; l < maxY; l++)
				{
					unsigned char r = im.pixels[k][l].getR();
					unsigned char g = im.pixels[k][l].getG();
					unsigned char b = im.pixels[k][l].getB();

					int norm = abs(rCrt - r) + abs(gCrt - g) + abs(bCrt - b);

					if(norm < ‍‍​‌‌﻿﻿​﻿threshold)
					{
						rAdd += r;
						gAdd += g;
						bAdd += b;
						voisinAdd++;
					}
				}
			}

			Color c = Color((unsigned char)(rAdd / voisinAdd), (unsigned char)(gAdd / voisinAdd), (unsigned char)(bAdd / voisinAdd));
			copy.pixels[i][j] = Pixel(c);

			rAdd = 0;
			gAdd = 0;
			bAdd = 0;
			voisinAdd = 0;
		}
	}
	return copy;
}
