#pragma once

#include "Object.h"
#include "Vector4.h"

namespace e3d {

class Material : public Object
{
private:
	Vector4 _color; //RGB COLOR
	string _name;

public:

	Material(double r,double g,double b,string n);
	Material(Material *mat);
	~Material(void);

	Vector4& getColor ()		 { return _color; }
	void setColor(Vector4 color) { _color = color; }
	string& getString()		     { return _name; }
	void setString(string& s)    { _name = s; }

};

}