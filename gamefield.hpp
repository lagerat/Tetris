
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
    std::vector<tetramino*> curAndNextTetra;
    int field[H][W];
public:
    virtual void checkCollisionInUp() = 0;
};


#endif //TETRIS_GAMEFIELD_HPP
