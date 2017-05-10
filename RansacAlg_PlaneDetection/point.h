#pragma once
using namespace std;

class point
{
public:
	double x, y, z, val;

	point(double xx, double yy, double zz, double value) {
		x = xx;
		y = yy;
		z= zz;
		val = value;
	}
	point() {}

};
