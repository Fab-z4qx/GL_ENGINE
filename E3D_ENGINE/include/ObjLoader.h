#pragma once

/* ObjLoader Classe */
/* Cette classe permet de charger en memoire un model 3D au format .obj */

#include <iostream>
#include <fstream>
#include <vector>
#include "Mesh.h"
#include "Polygone.h"
#include "Material.h"

using namespace std;

namespace e3d {

struct Vertex 
{
    int v, vt, vn;
    Vertex() {};
    Vertex(int v) : v(v), vt(v), vn(v) {};
    Vertex(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {};
};

class ObjLoader 
{
private:

	Mesh *_m;
	vector<Vector4> normal,texture,color;
	int fix_v(int index) { return(index > 0 ? index - 1 : (index == 0 ? 0 : (int)_m->getSize() + index)); }
    int fix_vt(int index) { return(index > 0 ? index - 1 : (index == 0 ? 0 : (int)texture.size() + index)); }
    int fix_vn(int index) { return(index > 0 ? index - 1 : (index == 0 ? 0 : (int)normal.size() + index)); }
    //vector< vector<Vertex> > curGroup;

     //int n_data;
     //double *vertice,*normals,*textures,*colours;
     //std::vector<Material*> materiaux;

public:
	ObjLoader();
	~ObjLoader(void);

	Vertex getInt3(const char*& token);
	Mesh* load(const string& name, const string& filename);
	void charger_mtl(string nom);
};

}

