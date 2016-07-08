#pragma once

#include "Screen.h"
#include "Config.h"

#if (RENDER_SYS == 3 || RENDER_SYS == 2 || RENDER_SYS == 4) //On regarde les options de compilation

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#if (RENDER_SYS == 4)
    #include <SFML/OpenGL.hpp>
#endif

using namespace sf;

namespace e3d {

class ScreenSFML : public Screen
{
private:
	sf::RenderWindow _window;
	vector<sf::Vertex> _line;
	vector<sf::Vertex> _point;
	vector<sf::Text> _label;
	sf::Font *_font; //On utilise la meme police partout

public:
	ScreenSFML(string name, int width, int height, int backgroundColor);
	~ScreenSFML(void);

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
#endif