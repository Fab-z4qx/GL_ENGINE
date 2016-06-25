#pragma once

/* La classe Entity */
/* Cette classe permet de representer un object à l'écran */
/* Une Entité est un ensemble de pts qui sont mobiles (herite de MovableObject) et transformables */

#include "movableobject.h"
#include "Mesh.h"

namespace e3d{

class Entity :public MovableObject
{
private:
	Vector4 _color; // On utilise les case 0,1,2 pour stocker les valeurs RGB de la couleur
	Mesh *_Mesh; //On associe un Ptr Mesh

public:
	Entity(const string& name, Mesh* MeshPtr);
	Entity(const string& name, Mesh* MeshPtr, const Vector4& color);
	Entity(const string& name, Mesh* MeshPtr, int red, int gree, int blue);
	~Entity(void);
	
	/* getter & setter */
	void setColor(Vector4 color) { _color = color; }
	void setColor(int red, int green, int blue) {
		_color.setX(red); _color.setY(green); _color.setZ(blue);
	}

	Vector4 getColor() { return _color; }
	Mesh* getMesh() { return _Mesh; }
	void attachMesh(Mesh *mesh) { _Mesh = mesh; }

	double getPointX(int at) { return _Mesh->getVertexAt(at).getX(); } 
	double getPointY(int at) { return _Mesh->getVertexAt(at).getY(); }
	double getPointZ(int at) { return _Mesh->getVertexAt(at).getZ(); }
	double getPointW(int at) { return _Mesh->getVertexAt(at).getW(); }

	Matrix operator*( Matrix& m){ return mult(m); };
	Vector4 operator*( Vector4& v){ return mult(v); };

};

}