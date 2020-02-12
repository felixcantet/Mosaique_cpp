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
// le dossier Input/SetImages/ contient toutes les images qui composeront la mosaique

int main()
{

	/////////////////////   Chargement des données    //////////////////////


	std::string pathMosaique;

	// ----------------- Demander le path de l'image a mosaiquer
	std::cout << "Indiquez le chemin de l image qui va etre mosaiquee : " << std::endl;
	std::cin >> pathMosaique;
	std::cout << "\n" << std::endl;
	
	// Loading de l'image à mosaiquer (input)
	Image inputImage((const char*)pathMosaique.c_str());
	
	// ----------------- Demander le nombre de raws et de column (limiter à X ?)
	std::cout << "Indiquez le nombre de ligne : " << std::endl;
	std::cin >> rows;
	
	std::cout << "Indiquez le nombre de colonne : " << std::endl;
	std::cin >> column;
	std::cout << "\n" << std::endl;

	// Calcule de la largeur et la hauteur des vignettes en pixel
	widthCrop = inputImage.getWidth() / column;
	heightCrop = inputImage.getHeight() / rows;

	// On resize l'image pour que ses dimensions soient multiple de column et rows
	inputImage = resize(inputImage, widthCrop * column, heightCrop * rows);

	//Decoupage de l'input

	// Les images découpés sont stockés dans un vector
	std::vector<Image> inputImageVignettes;
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			// Crop de chaque région
			Image tmp = cropRegion(inputImage, j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
			// Stockage de la région croppée
			inputImageVignettes.push_back(tmp);
		}
	}

	// ----------------- Demander le dossier contenant le set d'image (limiter à X ?)
	std::cout << "Indiquer le chemin du dossier contenant le set d images : " << std::endl;
	std::cin >> pathMosaique;
	std::cout << "\n" << std::endl;
	
	//Loading des vignette qui composeront la mosaique
	std::vector<Image> vignetteImages;

	// On récupère toutes les entrées dans le dossier indiqué par l'utilisateur
	auto d = fs::directory_iterator(pathMosaique);

	// On charge en mémoire une image pour chaque fichier dans le dossier
	// et on la stock dans notre vector
	for (const auto& entry : d)
	{
		// Ajouter un check de type de fichier pour ne prendre que les fichiers supportés
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
		// Si les dimensions de l'image sont supérieur à la dimension
		// d'une vignette, alors on la resize
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
			// On resize l'image
			vignetteImagesResize.push_back(resize(tmp, widthCrop, heightCrop));
			break;

		case 1:
			// Crop par le centre de l'image
			vignetteImagesResize.push_back(cropCenter(tmp, widthCrop, heightCrop));
			break;

		case 2:
			// Crop par le centre 
			vignetteImagesResize.push_back(cropCenter(tmp, widthCrop, heightCrop));
			// Crop par le coins
			vignetteImagesResize.push_back(crop(tmp, widthCrop, heightCrop));
			break;

		case 3:
			// Crop par le centre
			vignetteImagesResize.push_back(cropCenter(tmp, widthCrop, heightCrop));
			// Crop par le coin
			vignetteImagesResize.push_back(crop(tmp, widthCrop, heightCrop));
			// Resize
			vignetteImagesResize.push_back(resize(tmp, widthCrop, heightCrop));
			break;
		}
	}

	vignetteImages.clear();
	
	////////////////////////////  Génération de la mosaique    //////////////////////
	
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
		std::cout << "Quel poid voulez vous mettre pour la composante Hue ? (valeur flottante entre 0 et 1)" << std::endl;
		std::cin >> weightH;
		std::cout << "Quel poid voulez vous mettre pour la composante Saturation ? (valeur flottante entre 0 et 1)" << std::endl;
		std::cin >> weightS;
		std::cout << "Quel poid voulez vous mettre pour la composante Value ? (valeur flottante entre 0 et 1)" << std::endl;
		std::cin >> weightV;
	}
	//Comparaison des similitude + ajout de l'image dans chosenImages
	// Pour chaque partie de l'image d'input découpées
	for(int i = 0; i < inputImageVignettes.size(); i++)
	{
		// Initialisation de la valeur de similitude à Max
		int value = 999999;
		// Stockage de l'index ayant la plus petite différence
		int index = 0;
		// Pour chaque vignette de l'image
		for(int j = 0; j < vignetteImagesResize.size(); j++)
		{
			int currVal = 0;
			// Différence RGB
			if(similitudeAlgo == 1)
				currVal = diffVal(inputImageVignettes[i], vignetteImagesResize[j]);
			// Différence HSV
			else if(similitudeAlgo == 2)
				currVal = diffHSV(inputImageVignettes[i], vignetteImagesResize[j], weightH, weightS, weightV);
			// Différence par luminance (Histogramme)
			else if(similitudeAlgo == 3)
				currVal = diffLuminanceHisto(inputImageVignettes[i], vignetteImagesResize[j]);
			// Stockage du meilleur score et de l'image associée
			if(currVal <= value)
			{
				value = currVal;
				index = j;
			}
		}
		// On choisit l'image qui a le meilleur index
		chosenImages.push_back(vignetteImagesResize[index]);
	}

	//Construction de l'image final
	int index = 0;
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			// On modifie les pixels de l'image d'input pour la région donnée en paramtère
			// et en copiant l'image passée en paramètre
			inputImage.modifyPixelsRegion(chosenImages[index++], j * heightCrop, (j + 1) * heightCrop, i * widthCrop, (i + 1) * widthCrop);
		}
	}
	///////////////////////    Stockage de l'image   ///////////////////
	std::cout << "Ou veux tu enregistrer l image ? " << std::endl;
	std::cin >> pathMosaique;

	pathMosaique.append("finalIm.jpg");
	
	//L'image final est sauvegardée dans le dossier entré par l'utilisateur
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
