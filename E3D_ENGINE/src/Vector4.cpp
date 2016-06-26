#include "Vector4.h"
#include <cmath>

namespace e3d{

Vector4::Vector4(double x, double y, double z, double w)
{
	_v[0] = x; 
	_v[1] = y; 
	_v[2] = z; 
	_v[3] = w;
}


Vector4::Vector4(double s)
{
	_v[0] = _v[1] = _v[2] = 0.0;
	_v[3] = 1.0;
}

Vector4::~Vector4(void)
{

}

void Vector4::printf()
{
	cout << "x=" << _v[0] << endl;
	cout << "y=" << _v[1] << endl;
	cout << "z=" << _v[2] << endl;
	cout << "n=" << _v[3] << endl;
}

Vector4 Vector4::add(const Vector4&  x)
{
	return Vector4(_v[0] + x._v[0], _v[1] + x._v[1], _v[2] + x._v[2], _v[3] + x._v[3]);
}

Vector4 Vector4::operator+(const Vector4& x)
{
	return add(x);
}

Vector4 Vector4::sous(const Vector4&  x)
{
	return Vector4(_v[0] - x._v[0], _v[1] - x._v[1], _v[2] - x._v[2], _v[3] - x._v[3]);
}

Vector4 Vector4::operator-(const Vector4& x)
{
	return sous(x);
}

Vector4& Vector4::operator=(const Vector4& x)
{
	if (&x != this) {
		_v[0] = x._v[0]; 
		_v[1] = x._v[1]; 
		_v[2] = x._v[2];
		_v[3] = x._v[3]; 
	}
	return *this;
}

Vector4 Vector4::mult(const double& x) 
{
	return Vector4(_v[0] * x, _v[1] *x, _v[2] *x , _v[3] * x);
}

Vector4 Vector4::operator*(const double& x)
{
	return mult(x);
}

ostream& operator<<(ostream& os, const Vector4& x)
{
	os << "(" << x._v[0] << "," << x._v[1] << ","  << x._v[2] << "," << x._v[3] << ")"; 
	return os;
}

bool Vector4::isNull(const Vector4& x)
{
	if(_v[0] == 0 && _v[1] == 0 && _v[2] == 0 && _v[3] == 0)
		return 1;

return 0;
}

// A FINIR ! 
//Renvoi 1 si les vecteurs sont orthogonaux 0 sinon 
double Vector4::prodScal(const Vector4& x)
{
	if( isNull(*this) || isNull(x)) //SI un des deux vecteurs est null 
		return 1;
	else
		double norme = sqrt( _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] ); //racine(x²+y²+z²);
		double norme2 = sqrt( x._v[0] * x._v[0] + x._v[1] * x._v[1] + x._v[2] * x._v[2] );
		//double angle = (this * x)
	//	return (_v[0] + x._v[0], _v[1] + x._v[1], _v[2] + x._v[2], _v[3] + x._v[3]);
		return 0;
}

void Vector4::setValue(double x, double y, double z, double w)
{
	 _v[0] = x;
	 _v[1] = y;
	 _v[2] = z;
	 _v[3] = w;
}

void Vector4::setValueAt(int at, double x)
{
	_v[at] = x;
}

double Vector4::getValueAt(const int pos) const
{
	return _v[pos];
}


}