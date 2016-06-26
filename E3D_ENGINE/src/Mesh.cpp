#include "Mesh.h"

namespace e3d {

Mesh::Mesh(const string& name) : Object(name) {}

Mesh::~Mesh(void) {}

void Mesh::print()
{
	for (unsigned int i = 0; i < _vertex.size(); i++){
		cout << "[" << i << "]" ;
		cout << _vertex[i] << endl;
	}
}

ostream& operator<<(ostream& os, Mesh& m)
{
	for (unsigned int i = 0; i < m._vertex.size(); i++)
	{
		os << "[" << i << "]" ;
		os << m._vertex[i] << endl;
	}
	return os;
}


}