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

	std::vector<Image> vignetteImagesResize;
	
	//resize des vignette
	for (int i = 0; i < vignetteImages.size(); i++)
	{
		if (vignetteImages[i].getHeight() < heightCrop || vignetteImages[i].getWidth() < widthCrop)
		{
			vignetteImagesResize.push_back(Image(resize(vignetteImages[i], widthCrop, heightCrop)));
			continue;
		}

		int value = i % methodeUse;
		
		Image tmp(vignetteImages[i]);
		
		switch (value)
		{
		default:
			//vignetteImages[i] = resize(vignetteImages[i], widthCrop, heightCrop);
			vignetteImagesResize.push_back(resize(tmp, widthCrop, heightCrop));
			break;

		case 1:
			//vignetteImages[i] = cropCenter(vignetteImages[i], widthCrop, heightCrop);
			vignetteImagesResize.push_back(cropCenter(tmp, widthCrop, heightCrop));
			break;

		case 2:
			//vignetteImages[i] = cropCenter(vignetteImages[i], widthCrop, heightCrop);
			//vignetteImages[i] = crop(vignetteImages[i], widthCrop, heightCrop);
			vignetteImagesResize.push_back(cropCenter(tmp, widthCrop, heightCrop));
			vignetteImagesResize.push_back(crop(tmp, widthCrop, heightCrop));
			break;

		case 3:
			//vignetteImages[i] = cropCenter(vignetteImages[i], widthCrop, heightCrop);
			//vignetteImages[i] = crop(vignetteImages[i], widthCrop, heightCrop);
			//vignetteImages[i] = resize(vignetteImages[i], widthCrop, heightCrop);
			vignetteImagesResize.push_back(cropCenter(tmp, widthCrop, heightCrop));
			vignetteImagesResize.push_back(crop(tmp, widthCrop, heightCrop));
			vignetteImagesResize.push_back(resize(tmp, widthCrop, heightCrop));
			break;
		}
	}

	vignetteImages.clear();
	
	// ----------------- Enfin procéder
	
	//Declaration des image choisi
	std::vector<Image> chosenImages;
	int similitudeAlgo = 1;
	std::cout << "Quelle methode de similitude voulez vous utiliser ? \n" ;
	std::cout << "1 : Valeurs RGB \n";
	std::cout << "2 : Valeurs HSV \n";
	std::cout << "3 : Histogramme Luminance \n";
	std::cout << "Quelle methode de similitude voulez vous utiliser ? \n";
	std::cin >> similitudeAlgo;
	float weightH = 0;
	float weightS = 0;
	float weightV = 0;

	if (similitudeAlgo == 2) {
		std::cout << "Quel poid voulez vous mettre pour la composante H ? (valeur flottante entre 0 et 1" << std::endl;
		std::cin >> weightH;
		std::cout << "Quel poid voulez vous mettre pour la composante S ? (valeur flottante entre 0 et 1" << std::endl;
		std::cin >> weightS;
		std::cout << "Quel poid voulez vous mettre pour la composante V ? (valeur flottante entre 0 et 1" << std::endl;
		std::cin >> weightV;
	}
	//Comparaison des similitude + ajout de l'image dans chosenImages
	for(int i = 0; i < inputImageVignettes.size(); i++)
	{
		int value = 999999;
		int index = 0;
		for(int j = 0; j < vignetteImagesResize.size(); j++)
		{
			int currVal = 0;
			if(similitudeAlgo == 1)
				currVal = diffVal(inputImageVignettes[i], vignetteImagesResize[j]);
			else if(similitudeAlgo == 2)
				currVal = diffHSV(inputImageVignettes[i], vignetteImagesResize[j], weightH, weightS, weightV);
			else if(similitudeAlgo == 3)
				currVal = diffLuminanceHisto(inputImageVignettes[i], vignetteImagesResize[j]);
			
			if(currVal <= value)
			{
				value = currVal;
				index = j;
			}
		}

		chosenImages.push_back(vignetteImagesResize[index]);
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

	int radius = 2;
	int threshold = 128;
	int iteration = 2;
	
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
		std::cout << "Quel radius veux tu ? " << std::endl;
		std::cin >> radius;

		radius = radius > 12 ? 12 : radius <= 0 ? 1 : radius;
		
		std::cout << "Quel tolerance veux tu ? " << std::endl;
		std::cin >> threshold;

		threshold = threshold > 255 ? 255 : threshold <= 0 ? 0 : threshold;
		
		std::cout << "Combien d'iteration veux tu ? " << std::endl;
		std::cin >> iteration;

		iteration = iteration > 10 ? 10 : iteration <= 0 ? 1 : iteration;
		
		inputImage = meanshift(inputImage, radius, threshold, iteration);
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
