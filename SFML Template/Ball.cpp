#include "Ball.h"
#include <math.h>
#include <iostream>


int Ball::getSide() const
{
    return currentPos.x > playArea.width/2 ? 1 : currentPos.x < playArea.width/2 ? -1 : 0;
}

bool Ball::checkCollision(const sf::RectangleShape _Sprite)
{
    if (_Sprite.getGlobalBounds().contains(currentPos))
    {
        velocity.x = -velocity.x;
        currentPos += velocity;
        return true;
    }

    return false;
}

void Ball::update(const double _DT)
{
    int result = inBounds();
 
    if (result == 1)
        velocity.y = abs(velocity.y);
    else if (result == 3)
        velocity.y = -abs(velocity.y);

    currentPos += sf::Vector2f(velocity.x * _DT, velocity.y * _DT);
}

void Ball::render(sf::RenderTarget* _Target)
{
    sprite.setPosition(lerp(sprite.getPosition().x, currentPos.x, transitionTime), 
                       lerp(sprite.getPosition().y, currentPos.y, transitionTime));

    _Target->draw(sprite);
}

int Ball::inBounds()
{
    if (playArea.contains(currentPos))
        return 0;
    else
    {
        //Top of play area
        if (currentPos.y < playArea.top)
            return 1;
        //Bottom of play area
        else if (currentPos.y > playArea.top + playArea.height)
            return 3;

        //Left of play area
        if (currentPos.x < playArea.left)
            return 4;
        //Right if play area
        if (currentPos.x > playArea.left + playArea.width)
            return 2;
    }

    return 0;
}

float Ball::lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

Ball::Ball()
{
    setSize(5);
}

Ball::~Ball()
{
}

void Ball::setSize(const float _Size)
{
    sprite.setSize(sf::Vector2f(_Size, _Size));
    sprite.setOrigin(_Size / 2, _Size / 2);
}

void Ball::setPosition(const float _X, const float _Y)
{
    currentPos = sf::Vector2f(_X, _Y);
}

void Ball::setColor(const sf::Color _Color)
{
    sprite.setFillColor(_Color);
}

void Ball::setPlayArea(const sf::FloatRect _Area)
{
    playArea = _Area;
}

void Ball::setTransitionTime(const float _Time)
{
    transitionTime = _Time;
}

void Ball::setVelocity(const float _X, const float _Y)
{
    velocity.x = _X;
    velocity.y = _Y;
}

void Ball::speedMultiplier(const float _X, const float _Y)
{
    velocity.x *= _X;
    velocity.y *= _Y;
}

bool Ball::offPlayArea()
{
    return inBounds() == 2 || inBounds() == 4;
}

sf::Vector2f Ball::getVelocity() const
{
    return velocity;
}
