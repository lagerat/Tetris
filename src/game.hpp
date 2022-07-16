#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include "gamefield.hpp"
#include <ctime>

using namespace sf;


class game : public gamefield{
    const int delay = 500;
    bool tetraminoIsCreated = false;
    tetramino* current;
    int gameMenu(sf::RenderWindow& window);
public:
    int startGame();
    bool checkCollisonLRD(tetramino  *figure) override;
    void insertToVector(tetramino* cur);
    static inline int randTypeOfTetramino();
};




#endif //TETRIS_GAME_HPP
