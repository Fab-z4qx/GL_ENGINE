#include "Plane.h"

namespace e3d {

Plane::Plane(const string& name, double width, double height) : Mesh(name)
{
	_vertex.push_back(Vector4(0,0,0,1));
	_vertex.push_back(Vector4(width,0,0,1));
	_vertex.push_back(Vector4(0,0,height,1));
	_vertex.push_back(Vector4(width,0,height,1));
}

Plane::~Plane(void)
{

}


}