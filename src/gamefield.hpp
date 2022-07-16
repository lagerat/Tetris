
#ifndef TETRIS_GAMEFIELD_HPP
#define TETRIS_GAMEFIELD_HPP

#include "tetramino.hpp"


const int W = 10;
const int H = 20;

class gamefield {
protected:
    sf::Clock clockRotate;
    sf::Clock clockMoveX;
    sf::Clock instantFall;
    sf::Clock clockMoveY;
    std::vector<point*> pointsOnField;
    std::vector<point*> movedPoints;
    std::vector<point*>::iterator it = pointsOnField.begin();
    int field[H][W] = {0};
    sf::Texture background;
    sf::Texture windowTetris;
    sf::Sprite backgroundSprite;
    sf::Sprite windowTetrisSprite;
public:
    void checkAndDelLines(tetramino* &current);
    void loadTexture();
    virtual bool checkCollisonLRD(tetramino* figure) = 0;
};

#endif //TETRIS_GAMEFIELD_HPP
