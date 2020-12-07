
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
    std::vector<point*>::iterator it = pointsOnField.begin();
    int field[H][W] = {0};
public:
    void checkAndDelLines(){
        for (int i = 0; i < H ; ++i) {
            bool lineIsFull = true;
            for (int j = 0; j < W ; ++j) {
                if (field[i][j] == 0){
                    lineIsFull = false;
                    break;
                }
            }
            if (lineIsFull){
                for (int j = 0; j < W; ++j) {
                    field[i][j] = 0;
                }
                for (int j = 0; j < W ; ++j) {
                    for (it = pointsOnField.begin();it != pointsOnField.end(); ) {
                        if ((*it)->getX() == j && (*it)->getY() == i){
                            delete *it;
                            it = pointsOnField.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
                for (int j = i - 1; j > 0 ; --j) {
                    for (int k = 0; k < W  ; ++k) {
                        for (it = pointsOnField.begin();it != pointsOnField.end(); ) {
                            if ((*it)->getX() == k && (*it)->getY() == j){
                                (*it)->dropDown();
                                int tmp;
                                tmp = field[j][k];
                                field[j][k] = 0;
                                field[j+1][k] = tmp;
                            } else {
                                ++it;
                            }
                        }
                    }
                }
            }
        }
    }
    virtual bool checkCollisionInUp() = 0;
    virtual bool checkCollisonLRD(tetramino* figure) = 0;
};


#endif //TETRIS_GAMEFIELD_HPP
