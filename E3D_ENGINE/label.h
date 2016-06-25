#pragma once

/* Classe Label */
/* Represente un objet de type texte */
/* Un Label est composé d'un texte, d'une taille de police, d'une couleur */

#include <iostream>
#include "MovableObject.h"

using namespace std;

namespace e3d {

class Label :public MovableObject
{
private:
	string _label;
	unsigned int size; //Taille du texte
	Vector4 _color;

public:
	Label(string name, string value);
	Label(string name, string value, Vector4 color);
	Label(string name, string value, int red, int green, int blue);

	~Label(void);

	string	getLabel() { return _label; }
	void	setLabel(string s) { _label = s; }

	void	setColor(const Vector4& color) { _color = color; }
	void	setColor(int red, int green, int blue) {
		_color.setX(red); _color.setY(green); _color.setZ(blue);
	}
	Vector4& getColor() { return _color; }


};

}