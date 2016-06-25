

#ifndef __polygone__
#define __polygone__

#include <iostream>
#include <vector>
#include "Vector4.h"


namespace e3d {

class Polygone {
  
private:
	vector<unsigned int> _vertexIndice;

public:
    Polygone(); //default 3 index = 0
	~Polygone();
	Polygone(int a, int b, int c);
	Polygone(int a, int b, int c, int d);
	Polygone(int a, int b, int c, int d, int e);
	Polygone(int a, int b, int c, int d, int e, int f);
	int getPointAt(int i) { return _vertexIndice[i]; }
	void setPointAt(int i, int x) { _vertexIndice[i] = x; }
	size_t size() { return _vertexIndice.size(); }

	friend ostream& operator<<(ostream& os , const Polygone& p);

};
    
}

#endif /* defined(__openCV__polygone__) */
