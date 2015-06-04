#pragma once
/* ScreenOpenCV class */
/* Implementation de la classe Screen avec OpenCV */

#include "Config.h"

#if(RENDER_SYS==1 || RENDER_SYS==3)

#include "screen.h"
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace cv;

namespace e3d {

class ScreenOpenCV :public Screen
{
	double getPSNR ( const Mat& I1, const Mat& I2);
	Scalar getMSSIM( const Mat& I1, const Mat& I2);

private: 
	Mat _image; //Image pour le renduOpenCv

public:
	ScreenOpenCV::ScreenOpenCV(string screenName, int width, int height, int backgroundColor);
	~ScreenOpenCV(void);

	void init();
	void clean();
	void update();
	void drawLine( double p1, double p2, double p3, double p4, int red, int green, int blue);
	void drawPoint(double p1, double p2, double p3, double p4, int red, int green, int blue);
	void drawLabel(string label, double x, double y, int red, int green, int blue);
	void render();
};

}

#endif