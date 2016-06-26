#pragma once

/* Classe Cube */
/* Permet de representer un cube */
/* Un cube possede un largeur, hauteur, profondeur */
#include "mesh.h"

namespace e3d {

class Cube :public Mesh
{
private:
	double _width, _height, _Lenght;

public:
	Cube(const string& name,Vector4 center, double width, double height, double lenght);
	~Cube(void);
	
	double getWidth() { return _width; }
	double getHeight() { return _height; }
	double getLenght() { return _Lenght; }

	void print();
	friend ostream& operator<<(ostream&, Cube& c);
};

}