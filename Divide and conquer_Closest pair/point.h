#pragma once
using namespace std;

class point
{
public:
	double x, y, dist,p2x,p2y;

	point(double xx, double yy, double distance, double x2, double y2) {
		x = xx;
		y = yy;
		dist = distance;
		p2x = x2;
		p2y = y2;
	}
	point() {}

};
