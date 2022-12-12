#include "Game.h"
#include <time.h>

Game::Game()
{
	srand(time(nullptr));

	paused = true;
	leftScore = 0;
	rightScore = 0;

	font.loadFromFile("Font/font.ttf");
	gaussian.loadFromFile("gaussian.fs", sf::Shader::Fragment);

	leftText = sf::Text(std::to_string(leftScore), font, 30);
	leftText.setFillColor(sf::Color::White);
	leftText.setOutlineColor(sf::Color(100, 100, 100));

	rightText = sf::Text(std::to_string(rightScore), font, 30);
	rightText.setFillColor(sf::Color::White);
	rightText.setOutlineColor(sf::Color(100, 100, 100));
}

Game::~Game()
{
}

void Game::setSize(const sf::Vector2f _Size)
{
	windowSize = _Size;
	reset();
}

bool Game::ballOffSide()
{
	bool result = b1.offPlayArea();

	if (result)
	{
		int side = b1.getSide();

		if (side == -1)
		{
			rightScore++;
			rightText.setString(std::to_string(rightScore));
		}
		else if (side == 1)
		{
			leftScore++;
			leftText.setString(std::to_string(leftScore));
		}
	}

	return b1.offPlayArea();
}

void Game::updateEvents(sf::Event _Event)
{
	switch (_Event.type)
	{
	case sf::Event::KeyPressed:
		switch (_Event.key.code)
		{
		case Key::Space:
			paused = paused ? false : true;
			break;
		case Key::R:
			reset();
			break;
		}
		break;
	}
}

void Game::update(const double _DT)
{
	if (!paused)
	{
		p1.update(_DT);
		p2.update(_DT);
		b1.update(_DT);

		if (b1.checkCollision(*p1.getSprite()) ||
			b1.checkCollision(*p2.getSprite()))
		{
			b1.speedMultiplier(1.1f, 1.f);
		}
		//std::cout << _DT << std::endl;
		if (ballOffSide())
		{
			reset();
		}
	}
}

void Game::render(sf::RenderTarget* _Target)
{
	rightText.setOrigin(rightText.getGlobalBounds().width, 0);
	rightText.setPosition(windowSize.x - rightText.getGlobalBounds().width, 0);

	_Target->draw(rightText);
	_Target->draw(leftText);

	p1.render(_Target);
	p2.render(_Target);

	b1.render(_Target);

	//Bloom
	sf::RenderTexture t;
	p1.render(&t);
	p2.render(&t);


	b1.render(&t);

	for (int i = 0; i < 10; i++)
	{
		gaussian.setUniform("image", sf::Shader::CurrentTexture);
		gaussian.setUniform("horizontal", true);
	}

	sf::RenderStates states;
	states.shader = &gaussian;
	//states.blendMode = sf::BlendAdd;

	_Target->draw(sf::Sprite(t.getTexture()), states);
}

void Game::reset()
{
	float speed = 10;

	p1.setPosition(50, windowSize.y / 2);
	p1.setPlayArea(sf::Vector2f(0, windowSize.y));
	p1.setLength(50);
	p1.setWidth(10);
	p1.setSpeed(speed);

	p2.setPosition(windowSize.x - 50, windowSize.y / 2);
	p2.setPlayArea(sf::Vector2f(0, windowSize.y));
	p2.setLength(50);
	p2.setWidth(10);
	p2.setKeys(Key::Up, Key::Down);
	p2.setSpeed(speed);

	b1.setSize(5);
	b1.setPosition(windowSize.x / 2, windowSize.y / 2);
	b1.setTransitionTime(0.5f);
	b1.setColor(sf::Color::White);
	b1.setPlayArea(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	b1.setVelocity(rand() % 2 == 0 ? -3 : 3, rand() % 10 - 5);
}
