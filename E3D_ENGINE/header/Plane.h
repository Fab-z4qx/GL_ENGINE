#pragma once
#include "mesh.h"

namespace e3d {
class Plane : public Mesh
{
private:
	double _width, _height;
public:
	Plane(void);
	Plane(const string& name);
	Plane(const string& name, double width, double height);
	~Plane(void);
};

}