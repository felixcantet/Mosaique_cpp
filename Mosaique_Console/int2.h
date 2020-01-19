#pragma once
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
};