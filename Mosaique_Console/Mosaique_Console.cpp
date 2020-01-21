// Mosaique_Console.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <stdlib.h>
#include <iostream>

#include "Image.h"
#include <random>
#include <fstream>
#include <filesystem>

//namespace fs = std::experimental::filesystem;
namespace fs = std::filesystem;

int main()
{
	
	//// Snippet code for Load directory file
	//std::string path = "\Test";
	//auto d = fs::directory_iterator(path);
	//for (const auto& entry : d) {
	//	std::cout << entry.path() << std::endl;
	//	std::string p = entry.path().string();
	//	p.replace(p.begin(), p.end(), "'\'", '/');
	//	std::cout << p << std::endl;
	//}
	//
	//Image image = Image((const char*)"Test/Test.jpg");
	//std::cout << "Width : " << image.getWidth();
	//std::cout << "Height : " << image.getHeight();
	//std::cout << std::endl << image.getPixel(500, 500).getG();

	//Image image = Image((const char*)"Test/Test.jpg");
	Image* image = new Image(1000, 1000);
	
	std::cout << "Width : " << image->getWidth();
	std::cout << "Height : " << image->getHeight();
	//std::cout << std::endl << image.getPixel(150, 150).getG();

	for (int i = 0; i < image->getWidth(); i++)
	{
		for (int j = 0; j < image->getHeight(); j++)
		{
			int2* center = new int2(image->getWidth() / 2, image->getHeight() / 2);
			int2* current = new int2(i, j);
			float dist = center->dist(*current);
			if (dist < image->getWidth() / 4)
			{
				int2* pos = new int2(i, j);
				Color* col = new Color(30, 5, 56);
				image->pixels[i][j] = new Pixel(*pos, *col);
			}
			
			delete(center);
			delete(current);
		}
	}

	image->writeBackPixels();

	return 0;
}
