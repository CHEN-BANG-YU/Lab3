#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include<Eigen/Dense>
#include<Eigen/Sparse>
#define SIZE 18
using namespace std;
using namespace Eigen;
class polygon
{
public:
	Vector3d normal;
	Vector4d vertex[3];
	Vector3d color;
};

class Object {
public:
	vector<polygon> poly;
};


class Sphere
{
public:
	Vector3d center;
	double radius;
};


Object Modle(string name)
{
	Object OBJ;
	ifstream file(name,ios::in);
	string temp;
	polygon pol;

	while (!file.eof())
	{

		file >> temp;
		if (temp == "normal")
		{
			file >> pol.normal[0] >> pol.normal[1] >> pol.normal[2];
		}
		if (temp == "vertex" )
		{
			file >> pol.vertex[0][0] >> pol.vertex[0][1] >> pol.vertex[0][2];
			pol.vertex[0][3] = 1;
			file >> temp >> pol.vertex[1][0] >> pol.vertex[1][1] >> pol.vertex[1][2];
			pol.vertex[1][3] = 1;
			file >> temp >> pol.vertex[2][0] >> pol.vertex[2][1] >> pol.vertex[2][2];
			pol.vertex[2][3] = 1;
			OBJ.poly.push_back(pol);
		}
	}
	return	OBJ;
	file.close();
	
}

