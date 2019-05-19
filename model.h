#pragma once
#include <vector>
#include "geometry.h"
using namespace std;

class Model
{
private:
	vector<Vec3f> verts;
	vector<vector<int>> faces;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	vector<int> face(int idx);
};

