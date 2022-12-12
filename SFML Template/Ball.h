#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball();
	~Ball();

	void setSize(const float _Size);
	void setPosition(const float _X, const float _Y);
	void setColor(const sf::Color _Color);
	void setPlayArea(const sf::FloatRect _Area);
	void setTransitionTime(const float _Time);
	void setVelocity(const float _X, const float _Y);
	void speedMultiplier(const float _X, const float _Y);

	bool offPlayArea();
	sf::Vector2f getVelocity() const;
	//Get what side the ball is in
	//-1 left : 0 undefined : 1 right
	int getSide() const;

	bool checkCollision(const sf::RectangleShape _Sprite);

	virtual void update(const double _DT);
	void render(sf::RenderTarget* _Target);

private:
	//0 - In bounds
	//1 - Up
	//2 - Right
	//3 - Down
	//4 - Left
	int inBounds();
	float lerp(float, float, float);
	sf::Vector2f currentPos;
	sf::Vector2f velocity;
	float transitionTime;

	sf::FloatRect playArea;
	sf::RectangleShape sprite;
};

