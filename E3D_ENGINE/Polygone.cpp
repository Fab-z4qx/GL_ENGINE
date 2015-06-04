

#include "polygone.h"

namespace e3d {


Polygone::Polygone()
{
	_vertexIndice.push_back(0);
	_vertexIndice.push_back(0);
	_vertexIndice.push_back(0);
}

Polygone::Polygone(int a, int b, int c)
{
	_vertexIndice.push_back(a);
	_vertexIndice.push_back(b);
	_vertexIndice.push_back(c);
}


Polygone::Polygone(int a, int b, int c, int d)
{
	_vertexIndice.push_back(a);
	_vertexIndice.push_back(b);
	_vertexIndice.push_back(c);
	_vertexIndice.push_back(d);
}

Polygone::Polygone(int a, int b, int c, int d, int e)
{
	_vertexIndice.push_back(a);
	_vertexIndice.push_back(b);
	_vertexIndice.push_back(c);
	_vertexIndice.push_back(d);
	_vertexIndice.push_back(e);
}

Polygone::Polygone(int a, int b, int c, int d, int e, int f)
{
	_vertexIndice.push_back(a);
	_vertexIndice.push_back(b);
	_vertexIndice.push_back(c);
	_vertexIndice.push_back(d);
	_vertexIndice.push_back(e);
	_vertexIndice.push_back(f);
}
	
Polygone::~Polygone() 
{
	_vertexIndice.clear();
}

ostream& operator<<(ostream& os , const Polygone& p)
{
		os << "Polygone :  < ";
		for (int i = 0; i < p._vertexIndice.size(); i++)
		{
			if(i < p._vertexIndice.size()-1)
				os << p._vertexIndice[i] << " , " ;
			else
				os << p._vertexIndice[i] << " " ;
		}
		os << ">";
		return os;
	}
    
}