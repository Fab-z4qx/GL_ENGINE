#include "Cube.h"

namespace e3d {

Cube::Cube(const string& name,Vector4 center, double width, double height, double lenght):
	Mesh(name), _width(width), _height(height), _Lenght(lenght)
{
	_vertex.push_back(Vector4(center.getX()+width/2.0, center.getY()-height/2.0,center.getZ()-lenght/2.0,1));
    _vertex.push_back(Vector4(center.getX()+width/2.0, center.getY()+height/2.0,center.getZ()-lenght/2.0,1));
	_vertex.push_back(Vector4(center.getX()-width/2.0, center.getY()-height/2.0,center.getZ()-lenght/2.0,1));
	_vertex.push_back(Vector4(center.getX()-width/2.0, center.getY()+height/2.0,center.getZ()-lenght/2.0,1));

	_vertex.push_back(Vector4(center.getX()+width/2.0, center.getY()-height/2.0,center.getZ()+lenght/2.0,1));
	_vertex.push_back(Vector4(center.getX()+width/2.0, center.getY()+height/2.0,center.getZ()+lenght/2.0,1));
	_vertex.push_back(Vector4(center.getX()-width/2.0, center.getY()-height/2.0,center.getZ()+lenght/2.0,1));
	_vertex.push_back(Vector4(center.getX()-width/2.0, center.getY()+height/2.0,center.getZ()+lenght/2.0,1));

    // ajout des polygones
    _polygone.push_back(Polygone(2,1,3));
    _polygone.push_back(Polygone(3,4,2));
    
    _polygone.push_back(Polygone(8,7,5));
    _polygone.push_back(Polygone(5,6,8));
    
    _polygone.push_back(Polygone(1,5,7));
    _polygone.push_back(Polygone(7,3,1));
    
    _polygone.push_back(Polygone(6,2,4));
    _polygone.push_back(Polygone(4,8,6));
    
    _polygone.push_back(Polygone(6,5,1));
    _polygone.push_back(Polygone(1,2,6));
    
    _polygone.push_back(Polygone(4,3,7));
    _polygone.push_back(Polygone(7,8,4)); 
}

Cube::~Cube(void) {}

void Cube::print()
{
	for (unsigned int i = 0; i < _vertex.size(); i++)
	{
		cout << "[" << i << "]" ;
		cout << _vertex[i];
		cout << endl;
	}
}

ostream& operator<<(ostream& os, Cube& c)
{
	for (unsigned int i = 0; i < c._vertex.size(); i++)
	{
		os << "[" << i << "]" ;
		os << c._vertex[i];
		os << endl;
	}
	return os;
}


}