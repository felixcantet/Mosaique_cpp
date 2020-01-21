#ifndef _INT2_HPP_
#define _INT2_HPP_
#include <stdio.h>
#include <cmath>

struct int2 {
	int x;
	int y;

struct int2
{
	public:
		int x;
		int y;

		~int2() {};
	
		int2();
		int2(int x, int y);
		int2(int2& cop);

		int2& operator=(int2 cop);
		void swap(int2& cop);
	float dist(int2 p1) const {
		return sqrt(pow(x - p1.x, 2) + pow(y - p1.y, 2));
	}
};

#endif