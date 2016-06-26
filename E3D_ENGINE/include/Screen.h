#pragma once

//#include "OpenCV.h"
//#include "OpenGl.h"

#include <iostream> 
#include <string>  

using namespace std;

namespace e3d {

class Screen
{
protected:
	string _windowName;
	int _height;
	int _width;
	int _backgroundColor; //default = CV_8UC3 = black

public:
	Screen(string screenName="E3D Engine", int width=800, int height=800, int backgroundColor = 5);
	virtual ~Screen(void);
	virtual void init()=0;
	virtual void clean()=0;
	virtual void update()=0;
	virtual void drawLine ( double p1, double p2, double p3, double p4, int red, int green, int blue)=0;
	virtual void drawPoint( double p1, double p2, double p3, double p4, int red, int green, int blue)=0;
	virtual void drawLabel (std::string label, double x, double y, int red, int green,int blue)=0;
	virtual void render()=0;

	int getWidth() { return _width; }
	int getHeight() { return _height; }
};

}