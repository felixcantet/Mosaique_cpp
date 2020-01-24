// Mosaique_Console.cpp :
// Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.


#include <stdlib.h>
#include <iostream>

#include "Image.h"
#include <random>
#include <fstream>
#include <filesystem>
#include "croping.h"
#include "traitement.h"
#include <string>

namespace fs = std::experimental::filesystem;

int rows = 20;
int column = 20;

int vignetteNumber = 0;

int widthCrop = 0;
int heightCrop = 0;

// le dossier Input a à sa racine l'image à mosaiquer
// 
// le dossier Input/SetImages/ conteint toutes les images qui composeront la mosaique

int main()
{
	//Loading de l'image à mosaiquer (input)
	Image* image = new Image((const char*)"Input/loup.jpg");
	vignetteNumber = rows * column;

	//Calcule de la size des vignettes
	widthCrop = image->getWidth() / column;
	heightCrop = image->getHeight() / rows;

	//Decoupage de l'input
	std::vector<Image*> inputImageVignettes;
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			Image* tmp = cropRegion(*image, j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
			inputImageVignettes.push_back(tmp);
			
			std::string s = "Render/";
			s.append(std::to_string(i));
			s.append("_");
			s.append(std::to_string(j));
			s.append("inoutCrop.jpg");
			
			tmp->writeBackPixels(s.c_str());
		}
	}

	//Loading des vignette qui composeront la mosaique
	std::vector<Image*> vignetteImages;
	
	std::string path = "Input/SetImages/";
	auto d = fs::directory_iterator(path);
	
	for (const auto& entry : d) 
	{
		std::cout << entry.path() << std::endl;
		
		std::string p = entry.path().string();
		
		Image* test = new Image(p.c_str());
		
		std::cout << test->getHeight() << " " << test->getWidth() << std::endl;
		vignetteImages.push_back(test);
	}

	//resize des vignette
	for(int i = 0; i < vignetteImages.size(); i++)
	{
		if(vignetteImages[i]->getHeight() < heightCrop)
		{
			vignetteImages[i] = resize(*vignetteImages[i], widthCrop, heightCrop);
			continue;
		}
		
		switch (i)
		{
			
		default:
			vignetteImages[i] = resize(*vignetteImages[i], widthCrop, heightCrop);
			break;

		case 2:
			vignetteImages[i] = cropCenter(*vignetteImages[i], widthCrop, heightCrop);
			break;
		}
	}
	
	//Image* im2 = new Image((const char*)"Input/SetImages/input.jpg"); 
	
	std::cout << "Width : " << image->getWidth();
	std::cout << "Height : " << image->getHeight();

	//image = resize(*image, 800, 800);
	//image = luminance(*image);

	std::cout << "\n image croper ! " << std::endl;

	//L'image final est save dans le dossier render
	image->writeBackPixels("Render/resize.jpg");

	return 0;
}
