#include "Paddle.h"

Paddle::Paddle()
{
	setKeys(Key::Unknown, Key::Unknown);
}

Paddle::~Paddle()
{
}

void Paddle::setPosition(const float _X, const float _Y)
{
	currentPos = _Y;
	sprite.setPosition(_X, 0);
}

void Paddle::setWidth(const float _Width)
{
	sprite.setSize(sf::Vector2f(_Width, sprite.getSize().y));
	sprite.setOrigin(_Width/2, sprite.getSize().y/2);
}

void Paddle::setLength(const float _Length)
{
	sprite.setSize(sf::Vector2f(sprite.getSize().x, _Length));
	sprite.setOrigin(sprite.getSize().x/2, _Length/2);
}

void Paddle::setKeys(Key _Up, Key _Down)
{
	up = _Up;
	down = _Down;
}

void Paddle::setColor(const sf::Color _Color)
{
	sprite.setFillColor(_Color);
}

void Paddle::setSpeed(const float _Speed)
{
	speed = _Speed;
}

void Paddle::setTransitionSpeed(const float _Speed)
{
	transitionSpeed = _Speed;
}

void Paddle::setPlayArea(const sf::Vector2f _Area)
{
	limitArea = _Area;
}

sf::RectangleShape* Paddle::getSprite()
{
	return &sprite;
}

void Paddle::render(sf::RenderTarget* _Target)
{
	_Target->draw(sprite);

	updateSprite();
}

float Paddle::toPosition(const float _Y_Position)
{
	return lerp(currentPos, _Y_Position, transitionSpeed);
}

float Paddle::getPos() const
{
	return currentPos;
}

void Paddle::updateSprite()
{
	sprite.setPosition(sprite.getPosition().x, toPosition(currentPos));
}

float Paddle::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void Paddle::moveUp(const float _DT)
{
	currentPos -= speed * _DT;
}

void Paddle::moveDown(const float _DT)
{
	currentPos += speed * _DT;
}

int Paddle::inBounds()
{
	if (currentPos > 0 && currentPos < limitArea.y)
	{
		return 1;
	}
	else
	{
		if (currentPos < 0)
			return 0;
		else if (currentPos > limitArea.y)
			return -1;
	}
	return 1;
}
