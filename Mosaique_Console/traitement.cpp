﻿#include "traitement.h"

#include "Image.h"
#include <vector>
#include "utils.h"

Image* blanckWhite(Image& im)
{
	Image* newIm = &im;

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			float value = (newIm->pixels[i][j]->getR() + newIm->pixels[i][j]->getG() + newIm->pixels[i][j]->getB()) / 3;
			newIm->pixels[i][j] = new Pixel(*(new Color((int)value, (int)value, (int)value)));
		}
	}

	return newIm;
}

Image* blackOrWhite(Image& im)
{
	Image* newIm = blanckWhite(im);

	for (int i = 0; i < newIm->getWidth(); i++)
	{
		for (int j = 0; j < newIm->getHeight(); j++)
		{
			newIm->pixels[i][j] = newIm->pixels[i][j]->getR() >= 128 ? new Pixel(*new Color(255, 255, 255)) : new Pixel(*new Color(0, 0, 0));
		}
	}
	
	return newIm;
}

Image* meanshift(Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold, int iterations)
{
	Image* copy = new Image(im);
	
	for(int i = 0; i < iterations; i++)
	{
		copy = iterateMeanshift(*copy, radius, ‍‍​‌‌﻿﻿​﻿threshold);
	}

	return copy;
}

Image* iterateMeanshift(Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold)
{
	int voisinAdd = 0;
	int rAdd = 0;
	int gAdd = 0;
	int bAdd = 0;

	Image* copy = new Image(im);

	for(int i = 0; i < copy->getWidth(); i++)
	{
		for(int j = 0; j < copy->getHeight(); j++)
		{
			int minX = i - radius < 0 ? 0 : i - radius;
			int minY = j - radius < 0 ? 0 : j - radius;
			int maxX = i + radius + 1> copy->getWidth() ? copy->getWidth() : i + radius + 1;
			int maxY = j + radius + 1> copy->getHeight() ? copy->getHeight() : j + radius + 1;

			int rCrt = im.pixels[i][j]->getR();
			int gCrt = im.pixels[i][j]->getG();
			int bCrt = im.pixels[i][j]->getB();

			for(int k = minX; k < maxX; k++)
			{
				for (int l = minY; l < maxY; l++)
				{
					int r = im.pixels[k][l]->getR();
					int g = im.pixels[k][l]->getG();
					int b = im.pixels[k][l]->getB();

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

			Color* c = new Color((int)(rAdd / voisinAdd), (int)(gAdd / voisinAdd), (int)(bAdd / voisinAdd));
			copy->pixels[i][j] = new Pixel(*c);

			rAdd = 0;
			gAdd = 0;
			bAdd = 0;
			voisinAdd = 0;
		}
	}
	return copy;
}

/*
 *     for i in range(cop.size[0]):
            for j in range(cop.size[1]):
                #Calcule des voisins min et max
                minX = i - radius;
                if(minX < 0):
                    minX = 0
            
                minY = j - radius;
                if(minY < 0):
                    minY = 0 
            
                maxX = i + radius + 1;
                if(maxX >= cop.size[0]):
                    maxX = cop.size[0]
            
                maxY = j + radius + 1;
                if(maxY >= cop.size[1]):
                    maxY = cop.size[1]

                rCrt, gCrt, bCrt = pix[i,j]
            
                #recherche des voisins et addition de leur valeur
                for k in range(minX, maxX):
                    for l in range (minY, maxY):
                        r, g, b = pix[k,l‍‍​‌‌﻿﻿​﻿]
                        norm = abs(rCrt - r) + abs(gCrt - g) + abs(bCrt - b)#math.sqrt(math.pow(r - rCrt, 2) + \
                                #        math.pow(g - gCrt, 2) +  \
                                 #       math.pow(b - bCrt, 2))
                        if(norm < threshold):
                            rAdd += r
                            gAdd += g
                            bAdd += b
                            voisinAdd += 1
            
                #calcule de la nouvelle valeur
                newValue = (int(rAdd / voisinAdd), int(gAdd /voisinAdd), int(bAdd/voisinAdd))
                imgPix[i,j] = newValue
            
                #re initialisation des voisin
                voisinAdd = 0
                rAdd = 0
                gAdd = 0 
                bAdd = 0
                
    return cop;
    pass
 */