//Giorgos Raptakis
//Assignment 4-Graham Scan algorithm

#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <stack>
#include <stdlib.h>

#include "point.h"
#include "line.h"

using namespace std;

vector<point> random_points(int n, int min, int max);
int orientation(point , point , point );
bool compAngle(point , point);
double angle(point);
void swap(point, point );
point nextToTop(stack<point>);
stack<point> grahamScan(vector<point>);
void save_data(string filename, vector<point> , vector<point>);
	
int main() 
{
	//GENERATE RANDOM POINTS, arguments length and mix-max interval
	vector<point> Q = random_points(20, 0, 50);
	//return of function grahamScan()
	stack<point> hull = grahamScan(Q);

	vector<point> FinalPoint;
	while (!hull.empty())
	{
		point p = hull.top();
		cout << "(" << p.x << ", " << p.y << ")" << endl;
		FinalPoint.push_back(p);
		hull.pop();
	}

	save_data("C:/Users/Giorgos/Desktop/TU Berlin/3rd semester/Conception and Implementation of Spatial Analysis Methods/Lab4/ASS4_Raptaksi/final.txt", Q, FinalPoint);
	

	std::system("PAUSE");
	return 0;
}

// FUNCTIONS' IMPLEMENTATION //
vector<point> random_points(int n, int min, int max) {
	vector <point> p;
	point poin;
	int interval = (max - min + 1) + min;
	for (int i = 0; i != n; i++) {
		poin.x = (rand() % interval);
		poin.y = (rand() % interval);
		poin.angle = angle(poin);
		p.push_back(poin);
	}
	return p;
}

// To find orientation of ordered triplet
int orientation(point p1, point p2, point p3) {
		double dist = (p3.x - p1.x)*(p2.y - p1.y) - (p3.y - p1.y)*(p2.x - p1.x);
		if (dist == 0.0) { return 0; }//collinear
		else if (dist > 0.0) {return 1;}//clockwise
		else {return 2;	}//counterclockwise
	}

//If angles of points are the same then put 1st the point with lower X-value
bool compAngle(point pt1, point pt2) {
	if ((pt1.angle < pt2.angle)||((pt1.angle == pt2.angle) && (pt1.x <= pt2.x))) return true;
	else return false;
}

double angle(point p) {
	double angle = atan2(p.y - 0, p.x - 0) * 180 / M_PI ;
	return angle;
}
//swap two points
void swap(point p1, point p2) {
	point p = p1;
	p1 = p2;
	p2 = p;
}
//Find the point Next-To-Top in the stack
point nextToTop(stack<point> S) {
	point ptop = S.top();
	S.pop();
	point pnexttop = S.top();
	S.push(ptop);
	return pnexttop;
}
//Return convex hull of set of n points
stack<point> grahamScan(vector<point> Q) {
	stack<point> St;
	//find the point with lower Y-VALUE
	//if y-values the same then with the smaller x-value
	double minvalue = Q[0].y;
	int pos = 0;
	for (int i = 0; i != Q.size(); i++) {
		if (Q[i].y < minvalue || (Q[i].y == minvalue && Q[i].x < Q[pos].x))
		{
			minvalue = Q[i].y;
			pos = i;
		}
	}

	cout << "The initial point is in position: " << pos << " , with min Y-value =  " << minvalue << " , with min x-value =  " << Q[pos].x << endl;
	for (int i = 0; i < Q.size(); i++) {
		cout << Q[i].x << " " << Q[i].y << " " << Q[i].angle << endl;
	}
	// Place at first position the point with lower y-value
	swap(Q[0], Q[pos]);

	//sort of the vector
	sort(Q.begin(), Q.end(), compAngle);

	cout << "The Sorted Points are: " << endl;
	for (int i = 0; i < Q.size(); i++) {
		cout << Q[i].x << " " << Q[i].y << " " << Q[i].angle << endl;
	}

	//Check if two consecutive points have the same angle value, then keep the farther point from the p0
	for (int i = 1; i < Q.size() - 1; i++) {
		if (Q[i].angle == Q[i + 1].angle) {
			(Q[i].x <Q[i + 1].x) ? Q.erase(Q.begin() + i) : Q.erase(Q.begin() + i + 1);
		}
	}

	//if less than 3 points convex hull is not possible
	if (Q.size() <= 3) { return St; }

	// Create an empty stack and push first three points in it.
	St.push(Q[0]);
	St.push(Q[1]);
	St.push(Q[2]);

	for (int i = 3; i != Q.size(); i++) {
		if (orientation(nextToTop(St), St.top(), Q[i]) != 2) {
			St.pop();
			St.push(Q[i]);
		}
		else {
			St.push(Q[i]);
		}
	}
	return St;
}

	void save_data(string filename, vector<point> pts, vector<point> lString) {
		ofstream fileout;
		fileout.open(filename.c_str());
		fileout << "MULTIPOINT (";
		for (int i = 0; i != pts.size(); i++) {
			if (i == pts.size() - 1) {
				fileout << pts[i].x << " " << pts[i].y << ")" << endl;
			}
			else {
				fileout << pts[i].x << " " << pts[i].y << ",";
			}
		}
		fileout << "LINESTRING (";
		for (int i = 0; i != lString.size(); i++) {
			if (i == lString.size() - 1) {
				fileout << lString[i].x << " " << lString[i].y << ")" << endl;
			}
			else {
				fileout << lString[i].x << " " << lString[i].y << ",";
			}
		}
		fileout.close();
	}