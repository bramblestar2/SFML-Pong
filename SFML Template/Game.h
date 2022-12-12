#pragma once
#include "Ball.h"
#include "PlayerPaddle.h"

class Game
{
public:
	Game();
	~Game();

	void setSize(const sf::Vector2f _Size);
	bool ballOffSide();

	void updateEvents(sf::Event _Event);
	void update(const double _DT);
	void render(sf::RenderTarget* _Target);

private:
	void reset();

	sf::Vector2f windowSize;

	Ball b1;
	PlayerPaddle p1, p2;

	sf::Shader gaussian;
	sf::Font font;
	sf::Text leftText, rightText;

	bool paused;
	int leftScore, rightScore;
};
