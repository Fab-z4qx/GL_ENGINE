#include "label.h"

namespace e3d {

Label::Label(string name, string value) : MovableObject(name,e3d_label), _label(value) {}

Label::Label(string name, string value, Vector4 color) : MovableObject(name,e3d_label), _label(value), _color(color) {}

Label::Label(string name, string value, int red, int green, int blue) : MovableObject(name,e3d_label), _label(value) 
{
	_color.setX(red);
	_color.setY(green);
	_color.setZ(blue);
}

Label::~Label(void) {}

}