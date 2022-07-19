#include <iostream>
#include <SFML/Graphics.hpp>
#include "flask.h"
using namespace std;
/*
 * mini state manager
 * true - we keep a ball
 * false - we not keep a ball
 */
bool state = false;
bool win = false;
int cursor = 0;
Flask *flasks[4];
Ball *ball = nullptr;
void generate()
{
    Ball *ball;
    srand(time(0));
    for(int i = 0; i < 4; i++)
        flasks[i]->clear();
    for(int i = 0; i < 9; i++)
    {
        int num;
        bool canPut = true;
        while(canPut)
        {
            num = rand()%4;
            if(flasks[num]->getSize() != 3) canPut = !canPut;
        }
        switch(i)
        {
        case 0:
        case 1:
        case 2:
            ball = new Ball(sf::Color::Red);
            flasks[num]->put(*ball);
            break;
        case 3:
        case 4:
        case 5:
            ball = new Ball(sf::Color::Green);
            flasks[num]->put(*ball);
            break;
        case 6:
        case 7:
        case 8:
            ball = new Ball(sf::Color::Blue);
            flasks[num]->put(*ball);
            break;
        }
    }
}

bool checkWin()
{
    if(ball != nullptr)
        return false;
    for(int i = 0; i < 4; i++)
    {
        sf::Color currentColor = sf::Color::Black;
        for(auto a : flasks[i]->getStack())
        {
            if(flasks[i]->getStack().size() != 3)
                return false;
            if(currentColor == sf::Color::Black)
            {
                currentColor = a.color;
            }
            else
            {
                if(currentColor != a.color)
                    return false;
            }
        }
    }
    return true;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    sf::CircleShape triangle(40, 3);
    for(int i = 0; i < 4; i++)
    {
        flasks[i] = new Flask(250*i+25, 500);
        flasks[i]->setWindow(&window);
    }
    triangle.setFillColor(sf::Color::Cyan);
    generate();
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:

                if(event.key.code == sf::Keyboard::Enter)
                {
                    if(win)
                    {
                        delete ball;
                        ball = nullptr;
                        state = false;
                        generate();
                    }
                    else if(state)
                    {
                        if(flasks[cursor]->canPut())
                        {
                            state = !state;
                            flasks[cursor]->put(*ball);
                            delete ball;
                            ball = nullptr;
                        }
                    }
                    else
                    {
                        if(!flasks[cursor]->empty())
                        {
                            state = !state;
                            ball = flasks[cursor]->take();
                            ball->circle.setPosition(0, 0);
                        }
                    }
                }
                if(event.key.code == sf::Keyboard::Left)
                {
                    if(cursor == 0) cursor = 3;
                    else cursor--;
                }
                if(event.key.code == sf::Keyboard::Right)
                {
                    if(cursor == 3) cursor = 0;
                    else cursor++;
                }
                break;
            }
        }
        triangle.setPosition(cursor * 250+50, 810);
        win = checkWin();
        window.clear(sf::Color::White);
        window.draw(triangle);
        if(ball != nullptr)
            window.draw(*ball);
        for(int i = 0; i < 4; i++)
        {
            window.draw(*flasks[i]);
            flasks[i]->update();
        }
        window.display();
    }
}
