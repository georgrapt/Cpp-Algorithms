//Giorgos Raptakis
//Assignment 7

#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>

#include "point.h"
#include "line.h"

using namespace std;

vector<point> random_points(int n, int min, int max);
double SmallValue(double, double);
double distance(point, point);
bool smallerX(point, point);
bool smallerY(point, point);
void save_data(string filename, vector<point>,point);
double MinDistThreePoin(vector<point>);
double StripMinDist(vector<point>);
double TwoHalf(vector<point> points);

int main()
{
	clock_t start = clock();
	vector<point> pnt;
	//Random points
	pnt= random_points(20, 0, 50);

	//SORT points with x-values
	sort(pnt.begin(), pnt.end(), smallerX);
	for (int h = 0; h != pnt.size(); h++) {
		cout << " "<< pnt[h].x << ", " << pnt[h].y << " " << endl;
	}
	//Then minimum distance of a vector of points.
	double MinDist = TwoHalf(pnt);

	cout << "The minimum distance of our points are: "<<MinDist << "\n";
	
	cout << "Calculation of time:  " << start - clock_t() << endl;


	system("PAUSE");
	return 0;
}

// FUNCTIONS' IMPLEMENTATION //
bool smallerX(point pt1, point pt2) {
	if (pt1.x < pt2.x) return true;
	else return false;
}

bool smallerY(point pt1, point pt2) {
	if (pt1.y < pt2.y) return true;
	else return false;
}

double SmallValue(double v1, double v2) {
	return (v1 < v2) ? v1 : v2;
}

double distance(point p0, point p1) {
	if ((p0.x - p1.x) == 0) {
		return abs(p1.y - p0.y);
	} else if ((p0.y - p1.y )== 0) {
		return abs(p1.x - p0.x); }
	else {
		return sqrt((p1.x - p0.x)*(p1.x - p0.x) + (p1.y - p0.y)*(p1.y - p0.y)); }
}

vector<point> random_points(int n, int min, int max) {
	vector <point> p;
	point poin;
	int interval = (max - min + 1) + min;
	for (int i = 0; i != n; i++) {
		poin.x = (rand() % interval);
		poin.y = (rand() % interval);
		p.push_back(poin);
	}
	return p;
}

double MinDistThreePoin(vector<point> p) {
	double min = DBL_MAX;
	for (int i = 0; i < p.size(); ++i)
		for (int j = i + 1; j < p.size(); ++j)
			if (distance(p[i], p[j]) < min)
				min = distance(p[i], p[j]);
	return min;
}
 
double StripMinDist(vector<point> pnt) {
	sort(pnt.begin(), pnt.end(), smallerY);
	double min = DBL_MAX;
	for (int i = 0; i < pnt.size() - 1; ++i) {
		if (distance(pnt[i], pnt[i + 1]) < min) {
			min = distance(pnt[i], pnt[i + 1]);		}
	}
	return min;
}

double TwoHalf(const vector<point> points) {
	vector<point> subset_pointsRight, subset_pointsLeft;
	double dl, dr, d;
	int mediaPoint;
	if (points.size() > 3) {
		mediaPoint = static_cast<int>(points.size() / 2);
		point midPoint=points[mediaPoint];
		for (int i = 0; i <= mediaPoint; i++) {
			subset_pointsLeft.push_back(points[i]);
		}
		for (int i = mediaPoint; i != points.size(); i++) {
			subset_pointsRight.push_back(points[i]);
		}
		dl=TwoHalf(subset_pointsLeft);
		dr=TwoHalf(subset_pointsRight);
	}
	else {
		return MinDistThreePoin(points);
	}
	d= SmallValue(dl, dr);
	vector<point> strip;
	for (int i = 0; i != points.size(); i++) {
		if (abs(points[i].x - points[mediaPoint].x) < d) {
			strip.push_back(points[i]);
		}
	}
	return min(d, StripMinDist(strip));
}