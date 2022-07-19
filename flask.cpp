#include "flask.h"

Flask::Flask(int x, int y)
{
    this->x = x;
    this->y = y;
    texture.loadFromFile("flask.png");
    img.setTexture(texture);
    img.setPosition(x, y);
    ballPos = getY()+165;
}

void Flask::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(img, states);
}

bool Flask::put(Ball &ball)
{
    if(ballStack.size() != 3)
    {
        ball.circle.setPosition(getX()+15, ballPos);
        ballPos -= 120;
        ballStack.push_back(ball);
        return true;
    }
    else
        return false;
}

void Flask::setWindow(sf::RenderWindow *window)
{
    this->window = window;
}

void Flask::update()
{
    for(auto it : ballStack)
    {
        window->draw(it);
    }
}

Ball* Flask::take()
{
    Ball *ball = new Ball((*(ballStack.end()-1)).color);
    ballStack.pop_back();
    ballPos += 120;
    return ball;
}

bool Flask::canPut()
{
    if(ballStack.size() == 3)
        return false;
    else
        return true;
}

void Flask::clear()
{
    ballPos = getY()+165;
    ballStack.clear();
}

Ball::Ball(sf::Color color) : color(color)
{
    circle.setRadius(60);
    circle.setFillColor(color);
}
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle, states);
}
