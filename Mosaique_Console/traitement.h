#ifndef _TRAITEMENT_HPP_
#define _TRAITEMENT_HPP_
#include "Image.h"

Image* luminance(Image& im);
Image* blackOrWhite(Image& im);

Image* meanshift(Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold, int iterations);
Image* iterateMeanshift(Image& im, int radius, int ‍‍​‌‌﻿﻿​﻿threshold);

#endif
