#pragma once
#include "object.h"
#include "Matrix.h"

namespace e3d {

/* Constante qui permettent de differencier le type d'objet */
const unsigned int e3d_unknownObject=0;
const unsigned int e3d_movableObject=1;
const unsigned int e3d_entity=2;
const unsigned int e3d_rootNode=3;
const unsigned int e3d_node=4;
const unsigned int e3d_camera=5;
const unsigned int e3d_label=6;

class MovableObject : public Object, public Matrix {

private:
	bool _visible;
	int _type; //default = 0 => "Unknow object"
	string _name;

public:
	MovableObject(const string& name, int type); //Attends un nom, un type et ajoute l'objet dans le pool de la classe Object
	MovableObject(const string& name, const Vector4& pos);
	MovableObject(void);
	virtual ~MovableObject(void);

	/* Transformation */
	virtual void rotate(double angle, double x, double y, double z);
	virtual void rotateX(double angle);
	virtual void rotateY(double angle);
	virtual void rotateZ(double angle);
	virtual void translate(double x, double y, double z);
	virtual void scale(double x, double y, double z);
	
	/* Getter & setter */
	int  getType()		   { return _type; };
	void setType(int type) { _type = type; }

	bool isVisible()				{ return _visible; }
	void setVisibility(bool status) { _visible = status; }

	string getSetName()		  { return _name; }
	void setName(string name) {  _name = name; }

};

}