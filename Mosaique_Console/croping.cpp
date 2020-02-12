#include "croping.h"

Image crop(const Image &im, int w, int h)
{
	Image newIm(w, h);
	// On cr�e une nouvelle image en partant du pixel [0, 0]
	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			newIm.pixels[i][j] = im.pixels[i][j];
		}
	}

	return newIm;
}

Image cropCenter(const Image& im, int w, int h)
{
	Image newIm(w, h);

	// calcul des coordonn�s du centre de l'image
	int centerX = im.getWidth() / 2;
	int centerY = im.getHeight() / 2;

	// On retire la moiti� de la largeur et de la hauteur de la nouvelle image
	// pour que les deux images ai le m�me centre
	centerX -= w / 2;
	centerY -= h / 2;
	
	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			newIm.pixels[i][j] = im.pixels[i + centerX][j + centerY];
		}
	}

	return newIm;
}

Image cropRegion(const Image& im, int top, int bot, int left, int right)
{
	// Cr�ation d'une image � partir du rect donn� en param�tre
	Image newIm(right-left, bot-top);

	// On remplit le tableau de pixel en ajoutant les coordonn�s du rect
	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			newIm.pixels[i][j] = im.pixels[i + left][j+top];
		}
	}

	return newIm;
}

Image resize(const Image& im, int w, int h)
{
	Image newIm(w, h);

	// On calcule la position du pixel de la nouvelle image sur la l'image d'origine
	// en coordonn�e normalis�s (entre 0 et 1) 
	float coefX = (float)im.getWidth() / (float)newIm.getWidth();
	float coefY = (float)im.getHeight() / (float)newIm.getHeight();

	// On remplit chaque pixel de la nouvelle image en prenant la valeur 
	// du pixel de l'image d'origine aux coordonn�s donn�s
	for (int i = 0; i < newIm.getWidth(); i++)
	{
		for (int j = 0; j < newIm.getHeight(); j++)
		{
			// On multiplie i et j par le coef pr�c�demment calcul�
			int x = i * coefX;
			int y = j * coefY;
			newIm.pixels[i][j] = im.pixels[x][y];
		}
	}

	return newIm;
}
