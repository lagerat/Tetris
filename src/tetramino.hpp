#ifndef TETRIS_TETRAMINO_HPP
#define TETRIS_TETRAMINO_HPP

#include <iostream>
#include <SFML/Graphics.hpp>


class point{
private:
    int x;
    int y;
    sf::Sprite sprite;
public:
    bool isMoved = false;
    static sf::Texture texture;
    point();
    point(int nx, int ny);
    int getX() const;
    int getY() const;
    void setCoord(int x, int y);
    void setSprite(int color = 1);
    void dropDown();
    sf::Sprite& getSprite();
     virtual void drawSprite(sf::RenderWindow& window);
};



class tetramino : public point{
protected:
    int position[4] = {1,3,5,7};
    point* tetr[4];
public:
    tetramino();
    void moveLR(short turn, int oldCoord[][2]);
    void fallTetr(int oldCoord[][2]);

    virtual void rotate(int oldCoord[][2]);

    point* getTetr(int number);


    void drawSprite(sf::RenderWindow& window) override;
    void backOldCoord(int coords[][2]);
    virtual void setColor(){}
    virtual void setPos(){}
};

class ITetramino : public tetramino{
public:
    void setColor() override;
    void setPos() override;
    ITetramino();
};

class oTetramino : public tetramino{
public:
    oTetramino();

    void rotate(int oldCoord[][2]) override;
    void setColor() override;
    void setPos() override;
};

class sTetramino : public tetramino{
public:
    sTetramino();
    void setColor() override;
    void setPos() override;
};

class ZTetramino : public tetramino{
public:
    ZTetramino();
    void setColor() override;
    void setPos() override;
};

class LTetramino : public tetramino{
public:
    LTetramino();
    void setColor() override;
    void setPos() override;
};

class JTetramino : public tetramino{
public:
    JTetramino();
    void setColor() override;
    void setPos() override;
};

class tTetramino : public tetramino{
public:
    tTetramino();
    void setColor() override;
    void setPos() override;
};

#endif //TETRIS_TETRAMINO_HPP
