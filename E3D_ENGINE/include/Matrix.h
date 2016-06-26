#pragma once

/* Classe Matrix4 */
/* Cette classe represente une matrice en memoire */
/* Elle implemente donc les calcules matriciel de "base" */
/* Nous avons choisi de mettre cette classe en "friend" avec la classe Vector4 
pour permettre une utilisation plus facile des valeurs et ainsi eviter de passer par 
des getter et setter pour modifier les valeurs de notre matrice */

#include <iostream>
#include <limits>
#include "Vector4.h"

const double PI = 3.141592653589793238462;
namespace e3d{

class Matrix 
{
protected:
	Vector4 _m[4];
public:
	Matrix(void);
	Matrix(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
	Matrix(double x11, double x12, double x13, double w1,
			   double x21, double x22, double x23, double w2, 
			   double x31, double x32, double x34, double w3,
			   double x41, double x42, double x43, double w4);

	virtual ~Matrix(void);

	/* Calcule de base */
	Matrix add(const Matrix& m2) const ;  //Adiition de 2 matrices
	Matrix sous(const Matrix& m2) const ; //Soustraction de 2 matrices
	Matrix mult(const Matrix& m2) const ; //multiplication de 2 matrices
	Vector4 mult(const Vector4& v2) const ; //multiplication d'une matrice par un vector4

	// Afiche la matrice 
	void printf();

	//Renvoi la valeur à la case i,j de la matrice 
	//Par exemple m(1,2) <=> ligne 1, 2eme valeur
	double getValueAt(int i, int j) const;

	//Met la valeur x dans la case i,j de la matrice
	double setValueAt(int i, int j, double val);

	//Renvoi la matrice identité d'une matrice
	Matrix getMatIdentity();
	virtual void makeTransformation(const Matrix& m); //applique la transformation passé à l'objet 

	//TRANSLATION
	Matrix getTranslation(double x, double y, double z);
	Matrix getTranslation(Vector4& v);

	//SCALE 
	Matrix getScale(double x, double y, double z);
	Matrix getScale(Vector4& v);

	//ROTATE
	Matrix getRotate(double angle, double x, double y, double z);	
	Matrix getRotateX(double angle);
	Matrix getRotateY(double angle);
	Matrix getRotateZ(double angle);
 
	void setMat(const Matrix& x);
	const Matrix& getMat() { return *this; }
	
	Vector4 getVector4At(int i) { return _m[i]; } //Renvoi le vector de la ligne i

	virtual Matrix operator*(const Matrix& m) const { return mult(m); };
	virtual Vector4 operator*(const Vector4& v) const{ return mult(v); };
	virtual Vector4 operator*(const Vector4* v) const { return mult(*v); };
	Matrix operator-(const Matrix& m) const { return sous(m); };
	Matrix operator+(const Matrix& m) const { return add(m); };
	Matrix& operator=(const Matrix& x);
	bool operator==( const Matrix& m2 ) const;
	

	friend ostream& operator<<(ostream& os, const Matrix& m);
};

}