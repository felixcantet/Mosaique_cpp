// Mosaique_Console.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#include "std_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

//#include "Image.h"
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
	Image image = Image(2048, 2048);
	
	//std::cout << "Width : " << image->getWidth();
	//std::cout << "Height : " << image->getHeight();
	std::cout << std::endl << image.getPixel(150, 150).getG();

	for (int i = 0; i < image.getWidth(); i++) {
		for (int j = 0; j < image.getHeight(); j++) {
			int2* center = new int2(image.getWidth() / 2, image.getHeight() / 2);
			int2* current = new int2(i, j);
			float dist = center->dist(*current);
			if (dist < image.getWidth() / 4)
				image.pixelAcces[i][j] = Pixel(int2(i, j), Color(255, 0, 0));

			delete(center);
			delete(current);
		}
	}


	return 0;
}
