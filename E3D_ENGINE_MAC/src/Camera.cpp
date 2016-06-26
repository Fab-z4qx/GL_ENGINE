#include "Camera.h"

#ifdef __APPLE__
    #include <cmath>
#endif
namespace e3d {

/*fov l'angle d'ouverture 
la distance MIN : distance du plan "near" a la caméra 
la distance MAX : distance du plan "far" a la caméra */
Camera::Camera(string name, Vector4 position, double faR, double neaR, double foV) : 
	MovableObject(name,e3d_camera), _position(position), _far(faR), _near(neaR), _fov(foV) {}

Camera::~Camera(void) {}


//near = distance| far = Profondeur | fov = angle d'ouverture horizontale <=> Zoom
void Camera::getProject(const double Near, const double Far, const double fov, Matrix& r)
{
	double scale = 1 / tan((fov * 0.5)*(PI/180));
	r = Matrix(scale,0,0,0,
			0,scale,0,0,
			0,0,-Far/(Far -Near),-1,
			0,0, -(Far*Near)/(Far-Near),-1);
}


void Camera::getFrustum(double left, double right, double bottom, double top, double Near, double Far, Matrix &mat)
{
	mat = Matrix(2 * Near / (right - left), 0 , (right + left) / (right - left) , 0,
				0, 2 * Near / (top - bottom) , (top + bottom) / (top - bottom) , 0,
				0,0, -(Far + Near) / (Far - Near) , -2 * Far * Near / (Far - Near) ,
				0,0,-1,0);

	/* A MODIFIER SUIVANT L'ANGLE DE CAMERA VOULU */
	mat = mat * mat.getRotateX(PI);
	mat = mat * mat.getRotateY(PI/14);
}

/* Methode qui initialise la matrice de projection */
void Camera::getPerspective(double angle, double imageAspectRatio, double n, double f, Matrix &mat)
{
    double scale = tan((PI/180)*(angle * 0.5)) * n; 
    double r = imageAspectRatio * scale, l = -r;
    double t = scale, b = -t;
	getFrustum(l, r, b, t, n, f, mat);
}

}