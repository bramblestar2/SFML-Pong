#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle()
{
	Paddle::setKeys(Key::W, Key::S);
	Paddle::setWidth(5);
	Paddle::setLength(20);
	Paddle::setTransitionSpeed(0.1f);
	Paddle::setSpeed(10);
	Paddle::setColor(sf::Color::White);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::update(const double _DT)
{
	int result = Paddle::inBounds();
	if (result == 1)
	{
		if (sf::Keyboard::isKeyPressed(up))
			Paddle::moveUp(_DT);
		else if (sf::Keyboard::isKeyPressed(down))
			Paddle::moveDown(_DT);
	}
	else
	{
		if (result == 0)
			Paddle::moveDown(_DT);
		else if (result == -1)
			Paddle::moveUp(_DT);
	}
}
