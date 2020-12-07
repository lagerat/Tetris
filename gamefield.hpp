
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
    tetramino *curAndNextTetra[3];
    int field[H][W] = {0};
public:
    virtual bool checkCollisionInUp() = 0;
    virtual bool checkCollisonLRD(tetramino* figure) = 0;
};


#endif //TETRIS_GAMEFIELD_HPP
