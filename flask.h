#ifndef FLASK_H
#define FLASK_H
#include<SFML/Graphics.hpp>
#include<vector>
struct Ball : public sf::Drawable
{
    Ball(sf::Color);
    sf::Color color;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::CircleShape circle;
};

class Flask : public sf::Drawable
{
private:
    int x, y;
    int ballPos;
    sf::Texture texture;
    sf::Sprite img;
    std::vector<Ball> ballStack;
    sf::RenderWindow *window;
public:
    Flask(int x, int y);
    void setPosition(int x, int y);
    bool put(Ball &ball);
    void setWindow(sf::RenderWindow *window);
    int getX(){return x;} int getY(){return y;}
    int getSize(){return ballStack.size();}
    bool empty(){return ballStack.empty();}
    bool canPut();
    Ball* take();
    std::vector<Ball>& getStack(){return ballStack;}
    void clear();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update();
};

#endif // FLASK_H
