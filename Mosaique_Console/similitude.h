#pragma once
#include "Image.h"

int diffVal(const Image& im1, const Image& im2);

int diffHisto(const Image& im1, const Image& im2);

int diffLuminanceHisto(const Image& im1, const Image& im2);

int diffHSV(const Image& im1, const Image& im2, float weightH, float weightS, float weightV);