#pragma once

/* Class Mesh */
/* Represente un Mesh consitué d'un ensemble de points */
/* Un ensemble de polygones (face) */
/* Un ensemble de materiaux (Pour les textures) */

#include <vector>
#include <iostream>
#include "Object.h"
#include "Vector4.h"
#include "Polygone.h"
#include "Material.h"

using namespace std;

namespace e3d{

class Mesh : public Object
{
protected: 
	vector<Vector4> _vertex;
	vector<Polygone> _polygone;
	//vector<Material> _materiaux; //Tableau pour appliquer des textures à un objet
	int _visibility; //Mode d'affichage

public:
	Mesh(const string& name);
	virtual ~Mesh(void);

	void addVertex(Vector4 v)    { _vertex.push_back(v); }
	void setVisibility(int mode) { _visibility = mode; }
	int getVisibility()          { return _visibility; }

	size_t getSize()            { return _vertex.size(); }
	Vector4& getVertexAt(int i) { return _vertex[i]; }
	void setVertexAt(int i, const Vector4& x){ _vertex[i]= x; } 
	virtual void print();
	
	friend ostream& operator<<(ostream& os, Mesh& m);
    
    void addPolygone(const Polygone& p)  { _polygone.push_back(p); }
    size_t getNbPolygone()               { return _polygone.size() ; }
    Polygone& getPolygoneAt(int i)       { return _polygone[i] ; }
};


}
