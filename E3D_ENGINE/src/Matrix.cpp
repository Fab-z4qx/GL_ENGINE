
#include "Matrix.h"
#include <iomanip>

#if defined(__APPLE__) || defined (__MACH__)
    #include <cmath>
    #include <float.h>
#endif
#if defined (_WIN32) || defined (_WIN64)
    #include <omp.h>
#endif

namespace e3d {

Matrix::Matrix()
{ //Initialisation avec la matrice identitée
	_m[0] = Vector4(1.0, 0.0, 0.0, 0.0);
	_m[1] = Vector4(0.0, 1.0, 0.0, 0.0);
	_m[2] = Vector4(0.0, 0.0, 1.0, 0.0);
	_m[3] = Vector4(0.0, 0.0, 0.0, 1.0);
}

Matrix::Matrix(double x01, double x02, double x03, double w0,
			   double x11, double x12, double x13, double w1, 
			   double x21, double x22, double x23, double w2,
			   double x31, double x32, double x33, double w3) 
{
	_m[0] = Vector4(x01, x02, x03, w0);
	_m[1] = Vector4(x11, x12, x13, w1);
	_m[2] = Vector4(x21, x22, x23, w2);
	_m[3] = Vector4(x31, x32, x33, w3);
}

Matrix::Matrix(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4)
{
	_m[0] = v1;
	_m[1] = v2;
	_m[2] = v3;
	_m[3] = v4;
}

Matrix::~Matrix(void) {}

Matrix Matrix::getMatIdentity()
{
	return Matrix(Vector4(1.0,0.0,0.0,0.0),
				  Vector4(0.0,1.0,0.0,0.0), 
				  Vector4(0.0,0.0,1.0,0.0),
				  Vector4(0.0,0.0,0.0,1.0));
}

Matrix Matrix::getTranslation(double x, double y, double z)
{
	Matrix trans(1.0,0.0,0.0,x,
				0.0,1.0,0.0,y, 
				0.0,0.0,1.0,z,
				0.0,0.0,0.0,1.0); 

	return trans; 
}

Matrix Matrix::getTranslation(Vector4& v)
{
	Matrix trans(1.0,0.0,0.0,v._v[0],
				 0.0,1.0,0.0,v._v[1], 
				 0.0,0.0,1.0,v._v[2],
				 0.0,0.0,0.0,v._v[3]);

	return trans; 
}


Matrix Matrix::getScale(double x, double y , double z)
{
	Matrix trans(x,0.0,0.0,0.0,
				0.0,y,0.0,0.0, 
				0.0,0.0,z,0.0,
				0.0,0.0,0.0,1);

	return trans; 
}

Matrix Matrix::getScale(Vector4& v)
{
	Matrix trans(v._v[0],0.0,0.0,0.0,
				0.0,v._v[1],0.0,0.0, 
				0.0,0.0,v._v[2],0.0,
				0.0,0.0,0.0,v._v[3]);

	return trans; 
}

Matrix Matrix::getRotateX(double angle)
{
	Matrix trans(1,0,0,0,
				 0, cos(angle), -sin(angle), 0,
				 0, sin(angle), cos(angle),0,
				 0,0,0,1);
	return trans;
}

Matrix Matrix::getRotateY(double angle)
{
	Matrix trans(cos(angle),0,-sin(angle),0,
				 0, 1, 0, 0,
				 sin(angle), 0, cos(angle),0,
				 0,0,0,1);
	return trans;
}

Matrix Matrix::getRotateZ(double angle)
{
	Matrix trans(cos(angle),-sin(angle),0,0,
				 sin(angle), cos(angle),0,0,
				 0,0,1,0,
				 0,0,0,1);
	return trans;
}

void Matrix::makeTransformation(const Matrix& m)
{
	this->setMat(this->mult(m));
}

Matrix Matrix::getRotate(double angle, double x, double y, double z)
{
	if(x==1)
		return getRotateX(angle);
	else if(y==1)
		return getRotateY(angle);
	else
		return getRotateZ(angle);
}

/* Ici nous avons decider d'acceder directement au valeur des vector sans faire de boucle pour gagné en performance */
/*
inline Matrix Matrix::mult(const Matrix& m2) const
{
	Matrix r;
#pragma omp parallel sections
	{
		#pragma omp section
		{
		r._m[0]._v[0] = (_m[0]._v[0] * m2._m[0]._v[0]) + (_m[0]._v[1] * m2._m[1]._v[0]) + (_m[0]._v[2] * m2._m[2]._v[0]) + (_m[0]._v[3] * m2._m[3]._v[0]);
		r._m[0]._v[1] = (_m[0]._v[0] * m2._m[0]._v[1]) + (_m[0]._v[1] * m2._m[1]._v[1]) + (_m[0]._v[2] * m2._m[2]._v[1]) + (_m[0]._v[3] * m2._m[3]._v[1]);
		r._m[0]._v[2] = (_m[0]._v[0] * m2._m[0]._v[2]) + (_m[0]._v[1] * m2._m[1]._v[2]) + (_m[0]._v[2] * m2._m[2]._v[2]) + (_m[0]._v[3] * m2._m[3]._v[2]);
		r._m[0]._v[3] = (_m[0]._v[0] * m2._m[0]._v[3]) + (_m[0]._v[1] * m2._m[1]._v[3]) + (_m[0]._v[2] * m2._m[2]._v[3]) + (_m[0]._v[3] * m2._m[3]._v[3]);
		}

		#pragma omp section
		{
			r._m[1]._v[0] = (_m[1]._v[0] * m2._m[0]._v[0]) + (_m[1]._v[1] * m2._m[1]._v[0]) + (_m[1]._v[2] * m2._m[2]._v[0]) + (_m[1]._v[3] * m2._m[3]._v[0]);
			r._m[1]._v[1] = (_m[1]._v[0] * m2._m[0]._v[1]) + (_m[1]._v[1] * m2._m[1]._v[1]) + (_m[1]._v[2] * m2._m[2]._v[1]) + (_m[1]._v[3] * m2._m[3]._v[1]);
			r._m[1]._v[2] = (_m[1]._v[0] * m2._m[0]._v[2]) + (_m[1]._v[1] * m2._m[1]._v[2]) + (_m[1]._v[2] * m2._m[2]._v[2]) + (_m[1]._v[3] * m2._m[3]._v[2]);
			r._m[1]._v[3] = (_m[1]._v[0] * m2._m[0]._v[3]) + (_m[1]._v[1] * m2._m[1]._v[3]) + (_m[1]._v[2] * m2._m[2]._v[3]) + (_m[1]._v[3] * m2._m[3]._v[3]);
		}
		#pragma omp section
		{
			r._m[2]._v[0] = (_m[2]._v[0] * m2._m[0]._v[0]) + (_m[2]._v[1] * m2._m[1]._v[0]) + (_m[2]._v[2] * m2._m[2]._v[0]) + (_m[2]._v[3] * m2._m[3]._v[0]);
			r._m[2]._v[1] = (_m[2]._v[0] * m2._m[0]._v[1]) + (_m[2]._v[1] * m2._m[1]._v[1]) + (_m[2]._v[2] * m2._m[2]._v[1]) + (_m[2]._v[3] * m2._m[3]._v[1]);
			r._m[2]._v[2] = (_m[2]._v[0] * m2._m[0]._v[2]) + (_m[2]._v[1] * m2._m[1]._v[2]) + (_m[2]._v[2] * m2._m[2]._v[2]) + (_m[2]._v[3] * m2._m[3]._v[2]);
			r._m[2]._v[3] = (_m[2]._v[0] * m2._m[0]._v[3]) + (_m[2]._v[1] * m2._m[1]._v[3]) + (_m[2]._v[2] * m2._m[2]._v[3]) + (_m[2]._v[3] * m2._m[3]._v[3]);
		}
		#pragma omp section
		{
			r._m[3]._v[0] = (_m[3]._v[0] * m2._m[0]._v[0]) + (_m[3]._v[1] * m2._m[1]._v[0]) + (_m[3]._v[2] * m2._m[2]._v[0]) + (_m[3]._v[3] * m2._m[3]._v[0]);
			r._m[3]._v[1] = (_m[3]._v[0] * m2._m[0]._v[1]) + (_m[3]._v[1] * m2._m[1]._v[1]) + (_m[3]._v[2] * m2._m[2]._v[1]) + (_m[3]._v[3] * m2._m[3]._v[1]);
			r._m[3]._v[2] = (_m[3]._v[0] * m2._m[0]._v[2]) + (_m[3]._v[1] * m2._m[1]._v[2]) + (_m[3]._v[2] * m2._m[2]._v[2]) + (_m[3]._v[3] * m2._m[3]._v[2]);
			r._m[3]._v[3] = (_m[3]._v[0] * m2._m[0]._v[3]) + (_m[3]._v[1] * m2._m[1]._v[3]) + (_m[3]._v[2] * m2._m[2]._v[3]) + (_m[3]._v[3] * m2._m[3]._v[3]);
		}
	}
	return r;
}*/

inline Matrix Matrix::mult(const Matrix& m2) const
{
	Matrix r;

	r._m[0]._v[0] = (_m[0]._v[0] * m2._m[0]._v[0]) + (_m[0]._v[1] * m2._m[1]._v[0]) + (_m[0]._v[2] * m2._m[2]._v[0]) + (_m[0]._v[3] * m2._m[3]._v[0]);
	r._m[0]._v[1] = (_m[0]._v[0] * m2._m[0]._v[1]) + (_m[0]._v[1] * m2._m[1]._v[1]) + (_m[0]._v[2] * m2._m[2]._v[1]) + (_m[0]._v[3] * m2._m[3]._v[1]);
	r._m[0]._v[2] = (_m[0]._v[0] * m2._m[0]._v[2]) + (_m[0]._v[1] * m2._m[1]._v[2]) + (_m[0]._v[2] * m2._m[2]._v[2]) + (_m[0]._v[3] * m2._m[3]._v[2]);
	r._m[0]._v[3] = (_m[0]._v[0] * m2._m[0]._v[3]) + (_m[0]._v[1] * m2._m[1]._v[3]) + (_m[0]._v[2] * m2._m[2]._v[3]) + (_m[0]._v[3] * m2._m[3]._v[3]);

	r._m[1]._v[0] = (_m[1]._v[0] * m2._m[0]._v[0]) + (_m[1]._v[1] * m2._m[1]._v[0]) + (_m[1]._v[2] * m2._m[2]._v[0]) + (_m[1]._v[3] * m2._m[3]._v[0]);
	r._m[1]._v[1] = (_m[1]._v[0] * m2._m[0]._v[1]) + (_m[1]._v[1] * m2._m[1]._v[1]) + (_m[1]._v[2] * m2._m[2]._v[1]) + (_m[1]._v[3] * m2._m[3]._v[1]);
	r._m[1]._v[2] = (_m[1]._v[0] * m2._m[0]._v[2]) + (_m[1]._v[1] * m2._m[1]._v[2]) + (_m[1]._v[2] * m2._m[2]._v[2]) + (_m[1]._v[3] * m2._m[3]._v[2]);
	r._m[1]._v[3] = (_m[1]._v[0] * m2._m[0]._v[3]) + (_m[1]._v[1] * m2._m[1]._v[3]) + (_m[1]._v[2] * m2._m[2]._v[3]) + (_m[1]._v[3] * m2._m[3]._v[3]);

	r._m[2]._v[0] = (_m[2]._v[0] * m2._m[0]._v[0]) + (_m[2]._v[1] * m2._m[1]._v[0]) + (_m[2]._v[2] * m2._m[2]._v[0]) + (_m[2]._v[3] * m2._m[3]._v[0]);
	r._m[2]._v[1] = (_m[2]._v[0] * m2._m[0]._v[1]) + (_m[2]._v[1] * m2._m[1]._v[1]) + (_m[2]._v[2] * m2._m[2]._v[1]) + (_m[2]._v[3] * m2._m[3]._v[1]);
	r._m[2]._v[2] = (_m[2]._v[0] * m2._m[0]._v[2]) + (_m[2]._v[1] * m2._m[1]._v[2]) + (_m[2]._v[2] * m2._m[2]._v[2]) + (_m[2]._v[3] * m2._m[3]._v[2]);
	r._m[2]._v[3] = (_m[2]._v[0] * m2._m[0]._v[3]) + (_m[2]._v[1] * m2._m[1]._v[3]) + (_m[2]._v[2] * m2._m[2]._v[3]) + (_m[2]._v[3] * m2._m[3]._v[3]);

	r._m[3]._v[0] = (_m[3]._v[0] * m2._m[0]._v[0]) + (_m[3]._v[1] * m2._m[1]._v[0]) + (_m[3]._v[2] * m2._m[2]._v[0]) + (_m[3]._v[3] * m2._m[3]._v[0]);
	r._m[3]._v[1] = (_m[3]._v[0] * m2._m[0]._v[1]) + (_m[3]._v[1] * m2._m[1]._v[1]) + (_m[3]._v[2] * m2._m[2]._v[1]) + (_m[3]._v[3] * m2._m[3]._v[1]);
	r._m[3]._v[2] = (_m[3]._v[0] * m2._m[0]._v[2]) + (_m[3]._v[1] * m2._m[1]._v[2]) + (_m[3]._v[2] * m2._m[2]._v[2]) + (_m[3]._v[3] * m2._m[3]._v[2]);
	r._m[3]._v[3] = (_m[3]._v[0] * m2._m[0]._v[3]) + (_m[3]._v[1] * m2._m[1]._v[3]) + (_m[3]._v[2] * m2._m[2]._v[3]) + (_m[3]._v[3] * m2._m[3]._v[3]);
		
	return r;
}


/* Multiplication par un point */
Vector4 Matrix::mult(const Vector4& x) const
{
	Vector4 r;
	r._v[0] = _m[0]._v[0]*x._v[0] + _m[0]._v[1]*x._v[1] + _m[0]._v[2]*x._v[2] +  _m[0]._v[3]*x._v[3];
	r._v[1] = _m[1]._v[0]*x._v[0] + _m[1]._v[1]*x._v[1] + _m[1]._v[2]*x._v[2] +  _m[1]._v[3]*x._v[3];
	r._v[2] = _m[2]._v[0]*x._v[0] + _m[2]._v[1]*x._v[1] + _m[2]._v[2]*x._v[2] +  _m[2]._v[3]*x._v[3];
	r._v[3] = _m[3]._v[0]*x._v[0] + _m[3]._v[1]*x._v[1] + _m[3]._v[2]*x._v[2] +  _m[3]._v[3]*x._v[3];
	return r;
}

//Renvoi la valeur à la case i,j de la matrice 
//Par exemple m(1,2) <=> ligne 1, 2eme valeur
double Matrix::getValueAt(int i, int j) const
{
	if(i >= 0 && i <=3 && j >=0 && j <=3)
		return _m[i]._v[j];
	else
		return DBL_MIN; //ERREUR DE BORNES
}

double Matrix::setValueAt(int i, int j, double val)
{
	if(i >= 0 && i <=3 && j >=0 && j <=3)
	{
		_m[i]._v[j] = val;
		return 1;
	}
	else
		return DBL_MIN; //ERREUR DE BORNES
}

Matrix Matrix::add(const Matrix& m2) const
{
	Matrix r;
	r._m[0]._v[0] = _m[0]._v[0] + m2._m[0]._v[0];
	r._m[0]._v[1] = _m[0]._v[1] + m2._m[0]._v[1];
	r._m[0]._v[2] = _m[0]._v[2] + m2._m[0]._v[2];
	r._m[0]._v[3] = _m[0]._v[3] + m2._m[0]._v[3];

	r._m[1]._v[0] = _m[1]._v[0] + m2._m[1]._v[0];
	r._m[1]._v[1] = _m[1]._v[1] + m2._m[1]._v[1];
	r._m[1]._v[2] = _m[1]._v[2] + m2._m[1]._v[2];
	r._m[1]._v[3] = _m[1]._v[3] + m2._m[1]._v[3];

	r._m[2]._v[0] = _m[2]._v[0] + m2._m[2]._v[0];
	r._m[2]._v[1] = _m[2]._v[1] + m2._m[2]._v[1];
	r._m[2]._v[2] = _m[2]._v[2] + m2._m[2]._v[2];
	r._m[2]._v[3] = _m[2]._v[3] + m2._m[2]._v[3];

	r._m[3]._v[0] = _m[3]._v[0] + m2._m[3]._v[0];
	r._m[3]._v[1] = _m[3]._v[1] + m2._m[3]._v[1];
	r._m[3]._v[2] = _m[3]._v[2] + m2._m[3]._v[2];
	r._m[3]._v[3] = _m[3]._v[3] + m2._m[3]._v[3];
	return r;
}


Matrix Matrix::sous(const Matrix& m2) const
{
	Matrix r;
	r._m[0]._v[0] = _m[0]._v[0] - m2._m[0]._v[0];
	r._m[0]._v[1] = _m[0]._v[1] - m2._m[0]._v[1];
	r._m[0]._v[2] = _m[0]._v[2] - m2._m[0]._v[2];
	r._m[0]._v[3] = _m[0]._v[3] - m2._m[0]._v[3];

	r._m[1]._v[0] = _m[1]._v[0] - m2._m[1]._v[0];
	r._m[1]._v[1] = _m[1]._v[1] - m2._m[1]._v[1];
	r._m[1]._v[2] = _m[1]._v[2] - m2._m[1]._v[2];
	r._m[1]._v[3] = _m[1]._v[3] - m2._m[1]._v[3];

	r._m[2]._v[0] = _m[2]._v[0] - m2._m[2]._v[0];
	r._m[2]._v[1] = _m[2]._v[1] - m2._m[2]._v[1];
	r._m[2]._v[2] = _m[2]._v[2] - m2._m[2]._v[2];
	r._m[2]._v[3] = _m[2]._v[3] - m2._m[2]._v[3];

	r._m[3]._v[0] = _m[3]._v[0] - m2._m[3]._v[0];
	r._m[3]._v[1] = _m[3]._v[1] - m2._m[3]._v[1];
	r._m[3]._v[2] = _m[3]._v[2] - m2._m[3]._v[2];
	r._m[3]._v[3] = _m[3]._v[3] - m2._m[3]._v[3];
	return r;
}

void Matrix::printf()
{
	for (int i = 0; i < 4; i++)
	{
		cout << " | " ;
		for (int j = 0; j < 4; j++)
		{
			cout << this->getValueAt(i,j) << " ";
		}
		cout << "|" << endl;
	}
}

Matrix& Matrix::operator=(const Matrix& x)
{
	if (&x != this) 
	{

		_m[0].setX(x._m[0]._v[0]);
		_m[0].setY(x._m[0]._v[1]);
		_m[0].setZ(x._m[0]._v[2]);
		_m[0].setW(x._m[0]._v[3]);

		_m[1].setX(x._m[1]._v[0]);
		_m[1].setY(x._m[1]._v[1]);
		_m[1].setZ(x._m[1]._v[2]);
		_m[1].setW(x._m[1]._v[3]);

		_m[2].setX(x._m[2]._v[0]);
		_m[2].setY(x._m[2]._v[1]);
		_m[2].setZ(x._m[2]._v[2]);
		_m[2].setW(x._m[2]._v[3]);

		_m[3].setX(x._m[3]._v[0]);
		_m[3].setY(x._m[3]._v[1]);
		_m[3].setZ(x._m[3]._v[2]);
		_m[3].setW(x._m[3]._v[3]); 
	}
	return *this;
}

// SURCHARGE ? 
void Matrix::setMat(const Matrix& x)
{
	_m[0] = x._m[0];
	_m[1] = x._m[1];
	_m[2] = x._m[2];
	_m[3] = x._m[3];
}

bool Matrix::operator==( const Matrix& x) const
{
    if( 
		_m[0].getX() != x._m[0].getX() || _m[0].getY() != x._m[0].getY() || _m[0].getZ() != x._m[0].getZ()|| _m[0].getW() != x._m[0].getW() ||
		_m[1].getX() != x._m[1].getX() || _m[1].getY() != x._m[1].getY() || _m[1].getZ() != x._m[1].getZ()|| _m[1].getW() != x._m[1].getW() ||
        _m[2].getX() != x._m[2].getX() || _m[2].getY() != x._m[2].getY() || _m[2].getZ() != x._m[2].getZ()|| _m[2].getW() != x._m[2].getW() ||
        _m[3].getX() != x._m[3].getX() || _m[3].getY() != x._m[3].getY() || _m[3].getZ() != x._m[3].getZ()|| _m[3].getW() != x._m[3].getW() )
        return false;
    return true;
}


#define EPSILONE 0.000000001 //Permet de cast les valeur à l'affichage
ostream& operator<<(ostream& os, const Matrix& m)
{
		for (int i = 0; i < 4; i++)
		{
			os << " | " ;
			for (int j = 0; j < 4; j++)
			{
				if( abs(m.getValueAt(i,j)) < EPSILONE )
					os << "0 ";
				else
				os << std::setprecision(2) << m.getValueAt(i,j) << " ";
			}
			os << "|" << endl;
		}
		
	return os;
}


}