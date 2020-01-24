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
#include "similitude.h"

namespace fs = std::experimental::filesystem;

int rows = 50;
int column = 50;

int vignetteNumber = 0;

int widthCrop = 0;
int heightCrop = 0;

// le dossier Input a à sa racine l'image à mosaiquer
// 
// le dossier Input/SetImages/ conteint toutes les images qui composeront la mosaique

int main()
{
	//Loading de l'image à mosaiquer (input)
	Image* inputImage = new Image((const char*)"Input/loup.jpg");
	vignetteNumber = rows * column;

	//Calcule de la size des vignettes
	widthCrop = inputImage->getWidth() / column;
	heightCrop = inputImage->getHeight() / rows;

	inputImage = resize(*inputImage, widthCrop * column, heightCrop * rows);
	
	//Decoupage de l'input
	std::vector<Image*> inputImageVignettes;
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			Image* tmp = cropRegion(*inputImage, j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
			inputImageVignettes.push_back(tmp);
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

		case 3:
			vignetteImages[i] = cropCenter(*vignetteImages[i], widthCrop, heightCrop);
			break;
		}
	}

	//Declaration des image choisi
	Image** chosenImages = new Image* [column*rows];

	//Comparaison des similitude + ajout de l'image dans chosenImages
	for(int i = 0; i < inputImageVignettes.size(); i++)
	{
		int value = 999999;
		int index = 0;
		for(int j = 0; j < vignetteImages.size(); j++)
		{
			int currVal = diffVal(inputImageVignettes[i], vignetteImages[j]);
			if(currVal < value)
			{
				value = currVal;
				index = j;
			}
		}

		chosenImages[i] = new Image(*vignetteImages[index]);
	}

	//j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop
	
	//Construction de l'image final
	int index = 0;
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			inputImage->modifyPixelsRegion(chosenImages[index++], j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
		}
	}
	
	//L'image final est save dans le dossier render
	inputImage->writeBackPixels("Render/Mosaique.jpg");

	return 0;
}
