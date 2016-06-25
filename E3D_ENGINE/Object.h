#pragma once
/* Class Object */

#include <iostream>
#include <string>
#include <map>

using namespace std;
namespace e3d {

class Object
{
protected:
	static map<string,Object*> _pool; 
	static map<string,Object*>::iterator _ObjectIt;
private:
	string _name; //Nom appartenant à l'objet 

public:
	Object(void);
	Object(const string& name);
	Object(Object *x, const string& name);
	virtual ~Object(void);

	static void printPool();
	static void initPool();
    static void registerObject(Object* x, const string& name);
	static void registerObject(Object* x, const string* name);
	static void setObject(const string& name, Object *x);
	static map<string,Object*>* getMapObject() { return &_pool; };
	
	map<string,Object*>::iterator getObjectIt() const { return _ObjectIt; }
	void setObjectIt(map<string,Object*>::iterator val) { _ObjectIt = val; }

	static void cleanPool()					 { _pool.clear(); }
	static Object* find(const string& name)  { return _pool[name]; }
	static size_t count()                    { return _pool.size(); }

	string getName()						 { return _name; }
	Object* getObject(const string& name)    { return _pool[name]; }
	
	void unregisterObject(const string& name){ _pool.erase(name); }
};

}