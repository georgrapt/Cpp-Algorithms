#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iterator>
#include <cstdio>
#include <cmath>

#include "point.h"

using namespace std;

vector<point>  read_data(string);
void save_data(string filename, vector<point> pts);

void Ransac(vector<point>);
void Random3Pnt(vector<point>, double(&)[3][3], double);
void Plane_Param(double(&)[3][3], double(&plane)[4]);
string RandomColor();


int main() {
	srand(time(NULL));// to have different random number in each running
	vector<point> points;
	vector<point> data;

	points = read_data("C:/Users/Giorgos/Desktop/TU Berlin/3rd semester/Laser Scanning& 3D Measurement Techniques/Exercise2/Raptakis/Charite-large.ptx");
	cout << "Initial Number of points in the point cloud:" << points.size() << endl;


	//New vector of point with information
	for (auto m: points) {
		if (m.x == .0 && m.y == .0 && m.z == .0) continue;
		data.push_back(m);
	}
	
	cout << "\n Number of points after erazing zero coords: \t" << data.size() << endl;
	cout << endl;

	//Call the function of Ransac
	Ransac(data);

	cout << "\n Success termination of the Ransac Program \t " <<endl;

	system("PAUSE");
	return 0;
}

void Ransac(vector<point> data) {

	clock_t start = clock();
	//specify the parameters
	int Min_Num_Pnts_Chck =static_cast<int>(data.size()) *.08;   //remaining points,which above this tries STOP searching for a new plane
	double Max_Pln_Dist_Allw = 0.02;           //distance of a point and the plane
	int Min_Num_Pnts = static_cast<int>(data.size()) *.05;  //enough point to create a plane

	vector<point> Point_Plane;
	int plane_number = 0;
	int count_tries = 0; //Count the iteration in do-while loop
	int CountPointsInPlane;
	double Random3_Points[3][3];
	double (plane)[4];
	
	do {
		bool flag = false;
		Random3Pnt(data, Random3_Points, Max_Pln_Dist_Allw);
		Plane_Param(Random3_Points, plane);
		CountPointsInPlane = 0;

		double plane_norm = sqrt(pow(plane[0], 2) + pow(plane[1], 2) + pow(plane[2], 2));
		double DistPlane;

		for (int i = 0; i < data.size(); i++) {
			data[i].val = 0;
			//distance of a point and the plane
			DistPlane = abs((plane[0] * data[i].x + plane[1] * data[i].y + plane[2] * data[i].z + plane[3])) / plane_norm;
			if (DistPlane <=  Max_Pln_Dist_Allw) {
				CountPointsInPlane++;
				data[i].val = 1;
			}
		}
		if ((CountPointsInPlane - Min_Num_Pnts) > 0){ flag = true; }
			
		if (flag==true) {
			count_tries = 0;
			plane_number++;
			//Create new vector with points of the current Plane
			for (auto n : data) {
				if (n.val == 1) {
					Point_Plane.push_back(n);
				}
			}

			//Save the points of the specific plane
			string name = ("C:/Users/Giorgos/Desktop/TU Berlin/3rd semester/Laser Scanning& 3D Measurement Techniques/Exercise2/Raptakis/plane_" + to_string(plane_number) + ".txt");
			
			cout << " The data of new plane have been saved and have size of: \t" << Point_Plane.size() << endl;
			save_data(name, Point_Plane);

			//Erase from the initial DataSet the points that belongs to the plane
			for (vector<point>::iterator it = data.end()-1; it != data.begin() ; it--) {
				if (it->val == 1){
					it = data.erase(it);
				}
			}

			//Erase points that belong to thevector Point_Plane
			Point_Plane.clear();

			cout << "Remaining points after the plane creations are: \t" << data.size() << endl;
			cout << endl;
		}
		count_tries++;
	} while (data.size()>Min_Num_Pnts_Chck && count_tries<=250000);
		
	cout << "Calculation of time:  " << start - clock_t() << endl;

	save_data("C:/Users/Giorgos/Desktop/TU Berlin/3rd semester/Laser Scanning& 3D Measurement Techniques/Exercise2/Raptakis/RemainPoints.txt", data);
	cout << endl << "Save of remain points : " << data.size();

	if (count_tries > 250000) {
		cout << endl << "failed to detect another plane" << endl << "press enter to continue";
		cin.get();
	}
}
void Plane_Param(double(&point_coord)[3][3], double(&plane)[4]) {
	plane[0] = (point_coord[1][1] - point_coord[0][1])*(point_coord[2][2] - point_coord[0][2])
		- (point_coord[2][1] - point_coord[0][1])*(point_coord[1][2] - point_coord[0][2]);
	plane[1] = (point_coord[1][2] - point_coord[0][2])*(point_coord[2][0] - point_coord[0][0])
		- (point_coord[2][2] - point_coord[0][2])*(point_coord[1][0] - point_coord[0][0]);
	plane[2] = (point_coord[1][0] - point_coord[0][0])*(point_coord[2][1] - point_coord[0][1])
		- (point_coord[2][0] - point_coord[0][0])*(point_coord[1][1] - point_coord[0][1]);
	plane[3] = -(plane[0] * point_coord[0][0] + plane[1] * point_coord[0][1] + plane[2] * point_coord[0][2]);
	return;
}
void Random3Pnt(vector<point> data, double (&ThreePoint)[3][3], double thres) {
	int  p1, p2, p3;
	double dist1, dist2, dist3;
	do {
		p1 = rand() % data.size();
		p2 = rand() % data.size();
		p3 = rand() % data.size();

		dist1 = int(sqrt(pow((data[p1].x - data[p2].x), 2) + pow((data[p1].y - data[p2].y), 2)
			+ pow((data[p1].z - data[p2].z), 2)));
		dist2 = int(sqrt(pow((data[p1].x - data[p3].x), 2) + pow((data[p1].y - data[p3].y), 2)
			+ pow((data[p1].z - data[p3].z), 2)));
		dist3 = int(sqrt(pow((data[p2].x - data[p3].x), 2) + pow((data[p2].y - data[p3].y), 2)
			+ pow((data[p2].z - data[p3].z), 2)));
	}while ((p1 == p2 || p1 == p3 || p2 == p3)||(dist1<=5*thres || dist2<= 5* thres || dist3 <= 5* thres));


	ThreePoint[0][0] =(data[p1].x);
	ThreePoint[0][1] = (data[p1].y);
	ThreePoint[0][2] = (data[p1].z);
	ThreePoint[1][0] = (data[p2].x);
	ThreePoint[1][1] = (data[p2].y);
	ThreePoint[1][2] =(data[p2].z);
	ThreePoint[2][0] = (data[p3].x);
	ThreePoint[2][1] = (data[p3].y);
	ThreePoint[2][2] = (data[p3].z);
	
	return;
}

vector<point> read_data(string filename) {
	double x, y, z, value;
	vector<point> pts;
	ifstream filein;
	filein.open(filename.c_str());
	point pt;
	string line;
	while (getline(filein, line)) 
	{
		filein >> x >> y >> z >> value;
		pt.x = x;
		pt.y = y;
		pt.z = z;
		pt.val = value;
		pts.push_back(pt);
	}
	filein.close();
	return pts;
}
void save_data(string filename, vector<point> pts) {
	ofstream fileout;
	string red, green, blue;
	red =RandomColor();
	green = RandomColor();
	blue = RandomColor();
	fileout.open(filename.c_str());
	for (int i = 0; i < pts.size(); i++) {
		fileout << pts[i].x << " " << pts[i].y << " " << pts[i].z << " " << pts[i].val<< " " << red << " " << green << " " << blue << endl;
	}
	fileout.close();
}

string RandomColor() {
	int  rc;
	rc = 0+ rand() % (0-250);
		return to_string(rc);
}