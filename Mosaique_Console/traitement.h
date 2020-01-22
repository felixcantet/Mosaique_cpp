#ifndef  _TRAITEMENT_HPP_
#define _TRAITEMENT_HPP_

#include "Image.h"

// Ce fichier comporte toutes les fonctions de traitement pouvant être appliquées aux images

Image *crop(Image &im, int w, int h);
Image *cropCenter(Image& im, int w, int h);
Image* cropRegion(Image& im, int top, int bot, int left, int right);

Image* blanckWhite(Image& im);

#endif
