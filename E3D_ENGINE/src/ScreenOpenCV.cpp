#include "ScreenOpenCV.h"

#if(RENDER_SYS==1 || RENDER_SYS==3)

namespace e3d {
	ScreenOpenCV::ScreenOpenCV(string screenName, int width, int height, int backgroundColor) :
		Screen(screenName,width,height,backgroundColor)
{
	init();
}

ScreenOpenCV::~ScreenOpenCV(void)
{

}

void ScreenOpenCV::update()
{
	imshow( _windowName, _image );
	waitKey(1); 	
}

void ScreenOpenCV::clean()
{
	_image = Mat::zeros( _width, _height, _backgroundColor );
}

void ScreenOpenCV::init()
{
	_image = Mat::zeros( _width, _height, _backgroundColor ); //on init l'image avec la taille et la couleur de fond
	imshow( _windowName, _image ); //on affiche
	waitKey(1); //boucle
}

void ScreenOpenCV::drawLine( double p1, double p2, double p3, double p4, int red, int green, int blue)
{
  int thickness = 1;
  int lineType = 8;
  Scalar color(blue,green,red);
  line( _image,Point((int)p1,(int)p2),Point((int)p3,(int)p4),color,thickness,lineType );
}

void ScreenOpenCV::drawPoint(double p1, double p2, double p3, double p4, int red, int green, int blue)
{
  int thickness = 1;
  int lineType = 8;
  Scalar color(blue,green,red);
  line( _image,Point((int)p1,(int)p2),Point((int)p3,(int)p4),color,thickness,lineType );

}

void ScreenOpenCV::drawLabel(string label, double x, double y, int red,int green, int blue)
{
	CvPoint pt1 = cvPoint((int)x,(int)y);
	Scalar color = CV_RGB(red,green,blue);
	int scale = 1;
	putText(_image,label.c_str(),pt1,CV_FONT_HERSHEY_DUPLEX,scale,color);

}

void ScreenOpenCV::render()
{

}

}

#endif