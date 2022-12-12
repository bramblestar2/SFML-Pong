#include "Window.h"

Window::Window()
{
	initWindow();

	game.setSize(sf::Vector2f(window->getSize()));
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	window->clear(sf::Color(25,25,25));
	
	sf::RenderTexture t;
	t.create(window->getSize().x, window->getSize().y);

	game.render(&t);

	sf::Sprite s(t.getTexture());
	s.setPosition(0, window->getSize().y);
	s.setScale(1, -1);
	window->draw(s);

	window->display();
}

void Window::update()
{
	game.update(dt*70);
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
				window->close();
				break;
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
						window->close();
						break;
				}
				break;
		}

		game.updateEvents(event);
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 400), "Pong", sf::Style::Default);
	window->setFramerateLimit(60);
}
