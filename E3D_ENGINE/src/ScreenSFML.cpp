#include "ScreenSFML.h"

#if(RENDER_SYS == 2 || RENDER_SYS == 3)
namespace e3d {
ScreenSFML::ScreenSFML(string name, int width, int height, int backgroundColor) : 
	Screen(name,width,height,backgroundColor)
{
    init();
	_font = NULL; 
}

ScreenSFML::~ScreenSFML(void)
{
	_line.clear();
	_point.clear();
	_label.clear();
	delete(_font);
}

void ScreenSFML::init()
{
	sf::VideoMode vm(_height, _width);
	_window.create(vm, _windowName);
	_window.clear();
	_window.setFramerateLimit(0);
	
}

void ScreenSFML::render()
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

void ScreenSFML::clean()
{
	_window.clear(Color(0,0,0));
}


void ScreenSFML::update()
{
	sf::Event event;
	while (_window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			_window.close();
			exit(0);
		}
	}

	if(_line.size() != 0)
		_window.draw(&_line[0], (int)_line.size(), sf::Lines);
	if(_point.size() != 0)
		_window.draw(&_point[0], (int)_point.size(), sf::Points);

	if (!_label.empty()) {
		_window.draw(_label[0]);
	}

    _window.display();
	_line.clear(); //On vide les buffers
	_point.clear();
	_label.clear();
} 

void ScreenSFML::drawLine(double p1, double p2, double p3, double p4, int red, int green, int blue)
{
	_line.push_back(sf::Vertex(sf::Vector2f((float)p1, (float)p2), sf::Color(red,green,blue), sf::Vector2f((float)p1, (float)p2)));
	_line.push_back(sf::Vertex(sf::Vector2f((float)p3, (float)p4), sf::Color(red,green,blue), sf::Vector2f((float)p3, (float)p4)));
}

void ScreenSFML::drawPoint(double p1, double p2, double p3, double p4, int red, int green, int blue)
{
	_point.push_back(sf::Vertex(sf::Vector2f((float)p1, (float)p2), sf::Color(red,green,blue), sf::Vector2f((float)p1, (float)p2)));
	_point.push_back(sf::Vertex(sf::Vector2f((float)p3, (float)p4), sf::Color(red,green,blue), sf::Vector2f((float)p3, (float)p4)));
}

void ScreenSFML::drawLabel(string label, double x, double y, int red, int green, int blue)
{
	if(_font == NULL)
	{
		_font = new Font;
		if (!_font->loadFromFile("arial.ttf"))
		{
			cout << "Impossible d'ouvrir la police" << endl;
			//exit(0);
		}
	}

	/*
	sf::Text text;
	text.setFont(*_font); // font is a sf::Font

	// set the string to display
	text.setString(label.c_str());

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	sf::Color color(red,green,blue);
	text.setColor(color);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text.setPosition( (float)x, (float)y);

	_label.push_back(text);
	*/
}

}
#endif