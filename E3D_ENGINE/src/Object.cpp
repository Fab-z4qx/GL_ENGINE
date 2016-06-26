#include "Object.h"

namespace e3d {

std::map<string,Object*> Object::_pool;

Object::Object(void)
{

}

Object::Object(const string& name): _name(name)
{
	Object::registerObject(this,name); //On ajoute l'objet dans le pool
}

Object::Object(Object *x, const string& name): _name(name)
{
	Object::registerObject(x,name); //On ajoute l'objet dans le pool
}

Object::~Object(void)
{
	Object::unregisterObject(this->_name); //on supprime l'objet du pool
}

void Object::initPool()
{	
}

void Object::printPool()
{	
	cout << "Nombre d'objet dans le pool : " <<  _pool.size() << endl;
	for (map<string,Object*>::iterator it = _pool.begin(); it != _pool.end(); it++)
		cout << "[" << it->first << "]" << endl;
}


void Object::registerObject(Object* x, const string& name)
{
		if (_pool.find(name) == _pool.end())
			_pool[name] = x;
}

void Object::registerObject(Object* x, const string* name)
{
		if (_pool.find(*name) == _pool.end())
			_pool[*name] = x;
}

void Object::setObject(const string& name, Object *x) {
		_pool[name] = x;
}


} //namespace