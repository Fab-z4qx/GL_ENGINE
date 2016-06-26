#include "Material.h"

namespace e3d {

Material::Material(double r,double g,double b,string n): _name(n)
{
	_color.setX(r);
    _color.setY(g);
    _color.setZ(b);
}

Material::Material(Material *mat)
{
    _color = mat->_color;
    _name= mat->_name;
}

Material::~Material(void) {}

}