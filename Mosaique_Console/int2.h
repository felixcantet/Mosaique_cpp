#pragma once
#include <stdio.h>
#include <cmath>

struct int2 {
	int x;
	int y;

public:
	int2() {
		this->x = 0;
		this->y = 0;
	}

	int2(int x, int y) {
		this->x = x;
		this->y = y;
	}

	float dist(int2 p1) const {
		return sqrt(pow(x - p1.x, 2) + pow(y - p1.y, 2));
	}
};