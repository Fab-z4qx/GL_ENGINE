#include "ScreenGL.h"

namespace e3d {
    
    ScreenGL::ScreenGL(string name, int width, int height, int backgroundColor) : Screen(name,width,height,backgroundColor)
    {
        init();
    }
    
    ScreenGL::ScreenGL(void) : Screen()
    {
        init();
    }
    
    ScreenGL::~ScreenGL(void){
    }
    
    void ScreenGL::init()
    {
        sf::VideoMode vm(_height, _width);
        _window.create(vm, _windowName);
        _window.clear();
        _window.setFramerateLimit(60);
    }
    
    void ScreenGL::render()
    {
        clean();
        while (_window.isOpen())
        {
            sf::Event event;
            while (_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    _window.close();
            }
            update();
        }
        
    }
    
    void ScreenGL::clean()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void ScreenGL::update()
    {
        clean();
        sf::Event event;
        while (_window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                _window.close();
                exit(0);
            }
        }
  
        //glBegin(GL_LINES);
        if(!_line.empty())
        {
            double x = 1.0/_line.size();
            for(int i=0; i<_line.size(); i++)
            {
                glColor3d(1-(x*i), x*i ,1-(x*i));
                glVertex2d(_line.at(i).position.x, _line.at(i).position.y);
            }
            
        }
        //glEnd();
        
        glLoadIdentity();
        glOrtho(0, _width, 0, _height, -1, 1);
        //glLoadIdentity();
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_DOUBLE, 0, &_vertices[0]);
        
        glDrawArrays(GL_LINES, 0, _vertices.size());
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glFlush();

        
        if (!_label.empty()) {
            //_window.draw(_label[0]);
        }
        
        _window.display();
        _line.clear(); //On vide les buffers
        _point.clear();
        _label.clear();
        _vertices.clear();
    }
   
    
    void ScreenGL::drawLine(double p1, double p2, double p3, double p4, int red, int green, int blue)
    {
        
        _vertices.push_back(p1);
        _vertices.push_back(p2);
        _vertices.push_back(p3);
        _vertices.push_back(p4);
        
        //_line.push_back(sf::Vertex(sf::Vector2f((float)p1, (float)p2), sf::Color(red,green,blue), sf::Vector2f((float)p1, (float)p2)));
        //_line.push_back(sf::Vertex(sf::Vector2f((float)p3, (float)p4), sf::Color(red,green,blue), sf::Vector2f((float)p3, (float)p4)));
    }
    
    void ScreenGL::drawPoint(double p1, double p2, double p3, double p4, int red, int green, int blue)
    {
        
        /*
        _vertices.push_back(p1);
        _vertices.push_back(p2);
        _vertices.push_back(p3);
        _vertices.push_back(p4);
        */
        //_point.push_back(p1,p2);
        /*Point p;
        p.x = p1;
        p.y = p2;
        _point2.push_back(p);
        p.x = p3;
        p.y = p4;
        //_point2.push_back(p);*/
        //_point.push_back(sf::Vertex(sf::Vector2f((float)p1, (float)p2), sf::Color(red,green,blue)));
        //_point.push_back(sf::Vertex(sf::Vector2f((float)p3, (float)p4), sf::Color(red,green,blue)));
    }
    
    void ScreenGL::drawLabel(string label, double x, double y, int red, int green, int blue)
    {
      
    }
    
    
}
