#pragma once

/* Classe Camera */
/* Cette classe permet de calculer la projection des pts à un endroit donne dans une scene */

#include "Screen.h"
#include "ScreenSFML.h"
#include "ScreenOpenCV.h"
#include "MovableObject.h"

namespace e3d {

class Camera : public MovableObject
{
private:
	unsigned int _renderMode;
	Vector4 _position;
	double _far,_near,_fov;
	
public:
	
	//near € [0,1]
	Camera(string name, Vector4 position, double fov, double neaR, double faR);
	~Camera(void);

	/* Profondeur de champs */
	void setNear(double neaR) { _near = neaR; }
	double getNear() { return _near; }

	/* Distance du plan de projection */
	void setFar(double faR){ _far = faR; }
	double getFar() { return _far; }

	/* Angle horizontal de la camera */
	void setFov(double fov) { _fov = fov; }
	double getFov() { return _fov; }

	/*Modification de la position de la camera */
	void setPosition(const Vector4& val) { _position = val; }
	Vector4 getPosition() const { return _position; }

	/* Renvoi la matrice de projection en vue Perspective */
	void getProject(const double  Near, const double Far, const double fov, Matrix& r);
	
	/* Calcule de la projection des pts */
	void getPerspective(double angle, double imageAspectRatio, double n, double f, Matrix &mat);
	void getFrustum(double left, double right, double bottom, double top, double Near, double Far, Matrix &mat);

};

}