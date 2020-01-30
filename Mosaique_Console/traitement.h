#ifndef _TRAITEMENT_HPP_
#define _TRAITEMENT_HPP_
#include "Image.h"

Image luminance(const Image& im);
Image blackOrWhite(const Image& im);
Image sepia(const Image& im);
Image invertColor(const Image& im);

Image meanshift(const Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold, int iterations);
Image iterateMeanshift(const Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold);

#endif
