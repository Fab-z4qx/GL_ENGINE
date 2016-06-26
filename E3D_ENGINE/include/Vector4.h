#pragma once

#include <iostream>
using namespace std;

namespace e3d{
class Vector4
{
	friend class Matrix; //On ajoute la classe matrix en amis

protected:
	double _v[4];

public:
	Vector4(double x, double y, double z, double w);
	Vector4(double s=0.0);
	~Vector4(void);

	//methode 
	void printf();
	Vector4 add(const Vector4& x);
	Vector4 sous(const Vector4& x);
	Vector4 mult(const double& x);
	double prodScal(const Vector4& x);
	bool isNull(const Vector4& x);

	//Surchage operateurs 
	Vector4 operator-(const Vector4& x);
	Vector4 operator+(const Vector4& x);
	Vector4& operator=(const Vector4& x);
	Vector4 operator*(const double& x);
	
	friend ostream& operator<<(ostream& is, const Vector4& x);

	//Getter et Setter 
	void setValue(double x, double y, double z, double w);
	void setValueAt(int at, double x);

	double setX(double x)  { return _v[0] = x; }
	double setY(double y)  { return _v[1] = y; }
	double setZ(double z)  { return _v[2] = z; }
	double setW(double w)  { return _v[3] = w; }

	double getValueAt(const int pos) const;
	double getX() const { return _v[0]; }
	double getY() const { return _v[1]; }
	double getZ() const { return _v[2]; }
	double getW() const { return _v[3]; }
};

}