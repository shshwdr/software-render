#include "stdafx.h"
#include "model.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Model::Model(const char *filename)
{
	ifstream in;
	in.open(filename, ifstream::in);
	if (in.fail()) return;
	string line;
	while (!in.eof()) {
		getline(in, line);
		istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			Vec3f v;
			for (int i = 0;i < 3;i++) {
				iss >> v.raw[i];
			}
			verts.push_back(v);
		}
		else if (!line.compare(0, 2, "f ")) {
			//example for f:
			//f 1208/1256/1208 1088/1276/1088 1086/1257/1086
			//value start from 1
			vector<int> f;
			int itrash, idx;
			iss >> trash;
			while (iss >> idx >> trash >> itrash >> trash >> itrash) {
				idx--;
				f.push_back(idx);
			}
			faces.push_back(f);
		}
	}
}


Model::~Model()
{
}

int Model::nverts()
{
	return verts.size();
}

int Model::nfaces() {
	return faces.size();
}
vector<int> Model::face(int idx) {
	return faces[idx];
}
Vec3f Model::vert(int idx) {
	return verts[idx];
}
