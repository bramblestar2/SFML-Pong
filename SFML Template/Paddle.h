#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using Key = sf::Keyboard::Key;

class Paddle
{
public:
	Paddle();
	~Paddle();

	void setPosition(const float _X, const float _Y);
	void setWidth(const float _Width);
	void setLength(const float _Length);
	void setKeys(Key _Up, Key _Down);
	void setColor(const sf::Color _Color);
	void setSpeed(const float _Speed);
	void setTransitionSpeed(const float _Speed);
	void setPlayArea(const sf::Vector2f _Area);

	sf::RectangleShape* getSprite();

	virtual void update(const double _DT) = 0;
	void render(sf::RenderTarget* _Target);

protected:
	float toPosition(const float _Y_Position);
	float getPos() const;
	void updateSprite();
	void moveUp(const float _DT);
	void moveDown(const float _DT);

	//1 - InBounds
	//0 - less than x 
	//-1 - more than y
	int inBounds();

	Key up, down;

private:
	float lerp(float, float, float);

	sf::RectangleShape sprite;
	sf::Vector2f limitArea;

	float currentPos;
	float transitionSpeed;
	float speed;
};

