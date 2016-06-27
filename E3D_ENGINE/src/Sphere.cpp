#include "Sphere.h"

namespace e3d {
    
    Sphere::Sphere(const string& name,Vector4 center, double radius, double segments, double rings): Mesh(name)
    {
        const double PI = 3.141592653589793238462643383279502884197;
        this->_rings = rings;
        this->_segments = segments;
        if(segments == 0 || rings == 0)
        {
            rings = 30.0;
            segments = 30.0;
        }
        
        for(double theta = 0.; theta < 2*PI; theta += PI/segments)
        {
            for(double phi = 0.; phi < PI; phi += (PI/rings))
            {
                double x = center.getX() + cos(theta) * cos(phi) * radius;
                double y = center.getY() + cos(theta) * sin(phi) * radius;
                double z = center.getZ() + sin(theta) * radius;
                _vertex.push_back(Vector4(x,y,z,1));
            }
        }
        _polygone.push_back(Polygone(0,0,0,0));
    }
    
    Sphere::Sphere(const string& name,Vector4 center, double r, double n): Mesh(name)
    {
        int e;
        const double PI = 3.141592653589793238462643383279502884197;
        double segmentRad = PI / 2 / (n + 1);
        int numberOfSeparators = (int)(4 * n + 4);
        int p1,p2,p3;
        
        /* Vertex */
        for (e = -n; e <= n; e++)
        {
            double r_e = r * cos(segmentRad * e);
            double y_e = r * sin(segmentRad * e);
            
            for (int s = 0; s <= (numberOfSeparators - 1); s++)
            {
                double z_s = r_e * sin(segmentRad * s) * (-1);
                double x_s = r_e * cos(segmentRad * s);
                _vertex.push_back(Vector4(x_s,y_e,z_s,1));
            }
        }
        _vertex.push_back(Vector4(0,r,0,1));
        _vertex.push_back(Vector4(0,-r,0,1));
        
        /* Polygones */
        for (e = 0; e < 2 * n; e++)
        {
            for (int i = 0; i < numberOfSeparators; i++)
            {
                p1 = e * numberOfSeparators + i ;
                p2 = e * numberOfSeparators + i + numberOfSeparators ;
                p3 = e * numberOfSeparators + (i + 1) % numberOfSeparators + numberOfSeparators ;
                _polygone.push_back(Polygone(p1+1,p2+1,p3+1));
                
                p1 = e * numberOfSeparators + (i + 1) % numberOfSeparators + numberOfSeparators ;
                p2 = e * numberOfSeparators + (i + 1) % numberOfSeparators ;
                p3 = e * numberOfSeparators + i ;
                
                _polygone.push_back(Polygone(p1+1,p2+1,p3+1));
            }
        }
        
        for (int i = 0; i < numberOfSeparators; i++)
        {
            p1 = e * numberOfSeparators + i ;
            p2 = e * numberOfSeparators + (i + 1) % numberOfSeparators ;
            p3 = int(numberOfSeparators * (2 * n + 1));
            _polygone.push_back(Polygone(p1+1,p2+1,p3+1));
        }
        
        for (int i = 0; i < numberOfSeparators; i++)
        {
            p1 = i ;
            p2 = (i + 1) % numberOfSeparators ;
            p3 = int(numberOfSeparators * (2 * n + 1) + 1) ;
            _polygone.push_back(Polygone(p1+1,p2+1,p3+1));
        }
        
    }
    
    Sphere::~Sphere(void){}
    
}

