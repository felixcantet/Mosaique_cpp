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
#include "int2.h"
namespace fs = std::experimental::filesystem;

/*
 *friend inline Rational operator+(int value, const Rational& r)
    {
        Ra‍‍​‌‌﻿﻿​﻿tional rA(r);
        
        rA += value;
        
        return rA;
    }
 *
 *Rational &Rational::operator+=(const Rational& r)
{
    Rational tmp(r);
    
    if(this->m_den != tmp.m_den)
    {
        int myDen = this->m_den;
        
        this->m_den *= tmp.m_den‍‍​‌‌﻿﻿​﻿;
        this->m_num *= tmp.m_den;
        
        tmp.m_den *= myDen;
        tmp.m_num *= myDen;
    }
    
    this->m_num += tmp.m_num;
    
    simplify();
    
    return *this;
}
 * 
 */

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

	//for (int i = 0; i < image.getWidth(); i++) {
	//	for (int j = 0; j < image.getHeight(); j++) {
	//		if (i > 500)
	//			image.pixelAcces[i][j] = Pixel(int2(i, j), Color(255, 255, 0));
	//	}
	//}

	//image.writeBackPixels();


	return 0;
}
