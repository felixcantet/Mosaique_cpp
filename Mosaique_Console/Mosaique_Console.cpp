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

int rows = 256;
int column = 256;

int vignetteNumber = 0;

int widthCrop = 0;
int heightCrop = 0;

// le dossier Input a à sa racine l'image à mosaiquer
// 
// le dossier Input/SetImages/ conteint toutes les images qui composeront la mosaique

int main()
{
	std::string pathMosaique;

	// ----------------- Demander le path de l'image a mosaiquer
	std::cout << "Indiquer le chemin de l image qui va etre mosaiquer : " << std::endl;
	std::cin >> pathMosaique;
	std::cout << "\n" << std::endl;
	
	//Loading de l'image à mosaiquer (input)
	Image inputImage((const char*)pathMosaique.c_str());
	
	// ----------------- Demander le nombre de raws et de column (limiter à X ?)
	std::cout << "Indiquer le nombre de ligne : " << std::endl;
	std::cin >> rows;
	
	std::cout << "Indiquer le nombre de colonne : " << std::endl;
	std::cin >> column;
	std::cout << "\n" << std::endl;
	
	vignetteNumber = rows * column;

	//Calcule de la size des vignettes
	widthCrop = inputImage.getWidth() / column;
	heightCrop = inputImage.getHeight() / rows;

	inputImage = resize(inputImage, widthCrop * column, heightCrop * rows);

	//Decoupage de l'input
	std::vector<Image> inputImageVignettes;
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Image tmp = cropRegion(inputImage, j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
			inputImageVignettes.push_back(tmp);
		}
	}

	// ----------------- Demander le dossier contenant le set d'image (limiter à X ?)
	std::cout << "Indiquer le chemin du dossier contenant le set d images : " << std::endl;
	std::cin >> pathMosaique;
	std::cout << "\n" << std::endl;
	
	//Loading des vignette qui composeront la mosaique
	std::vector<Image> vignetteImages;

	auto d = fs::directory_iterator(pathMosaique);

	for (const auto& entry : d)
	{
		std::string p = entry.path().string();
		Image test(p.c_str());
		vignetteImages.push_back(test);
	}
	
	std::cout << "Set d images charger" << std::endl;
	std::cout << "\n" << std::endl;

	// ----------------- Demander le nombre de resize different ?
	int methodeUse = 1;
	std::cout << "Combien de methode de redimensionnement veux tu utiliser ? (maximum 3)" << std::endl;
	std::cin >> methodeUse;

	if (methodeUse <= 0)
		methodeUse = 1;
	
	if (methodeUse >= 3)
		methodeUse = 3;
	
	//resize des vignette
	for (int i = 0; i < vignetteImages.size(); i++)
	{
		if (vignetteImages[i].getHeight() < heightCrop || vignetteImages[i].getWidth() < widthCrop)
		{
			vignetteImages[i] = resize(vignetteImages[i], widthCrop, heightCrop);
			continue;
		}

		int value = i % methodeUse;
		
		switch (value)
		{

		default:
			vignetteImages[i] = resize(vignetteImages[i], widthCrop, heightCrop);
			break;

		case 0:
			vignetteImages[i] = cropCenter(vignetteImages[i], widthCrop, heightCrop);
			break;

		case 1:
			vignetteImages[i] = crop(vignetteImages[i], widthCrop, heightCrop);
			break;

		case 2:
			vignetteImages[i] = resize(vignetteImages[i], widthCrop, heightCrop);
			break;
		}
	}

	
	// ----------------- Enfin procéder
	
	//Declaration des image choisi
	std::vector<Image> chosenImages;

	//Comparaison des similitude + ajout de l'image dans chosenImages
	for(int i = 0; i < inputImageVignettes.size(); i++)
	{
		int value = 999999;
		int index = 0;
		for(int j = 0; j < vignetteImages.size(); j++)
		{
			int currVal = diffVal(inputImageVignettes[i], vignetteImages[j]);
			if(currVal <= value)
			{
				value = currVal;
				index = j;
			}
		}

		chosenImages.push_back(vignetteImages[index]);
	}

	//Construction de l'image final
	int index = 0;
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			inputImage.modifyPixelsRegion(chosenImages[index++], j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
		}
	}

	std::cout << "Ou veux tu enregistrer l image ? " << std::endl;
	std::cin >> pathMosaique;

	pathMosaique.append("finalIm.jpg");
	
	//L'image final est save dans le dossier render
	inputImage.writeBackPixels(pathMosaique.c_str());

	chosenImages.clear();

	vignetteImages.clear();
	inputImageVignettes.clear();

	std::cout << "\n Image Mosaiquer ! \n" << std::endl;

	std::cout << "Veux tu appliquer un filtre a ta nouvelle images ? : \n";
	std::cout << "0 - Luminance \n";
	std::cout << "1 - Blanc ou Noir \n";
	std::cout << "2 - Sepia \n";
	std::cout << "3 - Inversion de couleur \n";
	std::cout << "4 - Meanshift \n";
	std::cout << "5 - Rien \n";
	int filtre = 5;

	std::cin >> filtre;

	filtre = filtre > 5 ? 5 : filtre <= 0 ? 0 : filtre;

	switch (filtre)
	{
	case 0:
		inputImage = luminance(inputImage);
		break;

	case 1:
		inputImage = blackOrWhite(inputImage);
		break;

	case 2:
		inputImage = sepia(inputImage);
		break;

	case 3:
		inputImage = invertColor(inputImage);
		break;

	case 4:
		inputImage = meanshift(inputImage, 2, 127, 2);
		break;

	case 5:
		break;
	}

	if(filtre != 5)
	{
		pathMosaique.append("filtrage.jpg");
		inputImage.writeBackPixels(pathMosaique.c_str());
	}

	return 0;
}
