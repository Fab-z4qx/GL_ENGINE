#include "MovableObject.h"

namespace e3d{

MovableObject::MovableObject(const string& name,int type) : Object(name), Matrix()
{
	this->_name = name;
	this->_type = type;
	this->_visible = true;
}

MovableObject::MovableObject(const string& name, const Vector4& pos) : Object(name), Matrix()
{
	this->_name = name;
	this->_visible = true;
}

MovableObject::~MovableObject(void) {}

void MovableObject::translate(double x, double y, double z)
{
	this->setMat(this->mult(this->getTranslation(x,y,z)));
}

void MovableObject::rotate(double angle, double x, double y, double z)
{
	if(x==1)
		this->setMat(this->mult(this->getRotateX(angle)));
	else if(y==1)
		this->setMat(this->mult(this->getRotateY(angle)));
	else
		this->setMat(this->mult(this->getRotateZ(angle)));
}

void MovableObject::rotateX(double angle)
{
	this->setMat(this->mult(this->getRotateX(angle)));
}

void MovableObject::rotateY(double angle)
{
	this->setMat(this->mult(this->getRotateY(angle)));
}

void MovableObject::rotateZ(double angle)
{
	this->setMat(this->mult(this->getRotateZ(angle)));
}

void MovableObject::scale(double x, double y, double z)
{
	this->setMat(this->mult(this->getScale(x,y,z)));
}

}
