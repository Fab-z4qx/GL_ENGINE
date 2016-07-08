#pragma once

#include "Screen.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;

namespace e3d {
    
    class ScreenGL : public Screen
    {
    private:
        sf::RenderWindow _window;
        vector<sf::Vertex> _line;
        vector<sf::Vertex> _point;
        
        typedef struct Point{
            double x;
            double y;
        }Point;
        
        vector<Point> _point2;
        
        vector<sf::Text> _label;
        sf::Font *_font; //On utilise la meme police partout
        
        
    public:
        ScreenGL(string name, int width, int height, int backgroundColor);
        ScreenGL(void);
        ~ScreenGL(void);
        
        void init();
        void clean();
        void update();
        void drawLine( double p1, double p2, double p3, double p4, int red, int green, int blue);
        void drawPoint(double p1, double p2, double p3, double p4, int red, int green, int blue);
        void drawLabel(string label, double x, double y, int red, int green, int blue);
        int isOpen() { return _window.isOpen(); }
        void render();
    };
    
}