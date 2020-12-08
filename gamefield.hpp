
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
    void checkAndDelLines(tetramino* &current){
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
                                bool isUnique = true;
                                for (int l = 0; l < movedPoints.size(); ++l) {
                                    if (movedPoints[i] == (*it)){
                                        isUnique = false;
                                    }
                                 }
                                if (isUnique){
                                    movedPoints.push_back(*it);
                                }
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
        if (movedPoints.size() > 0){
            for (int j = 0; j < movedPoints.size(); ++j) {
                bool needToMove = true;
                for (int i = 0; i < 4; ++i) {
                   if ( current->getTetr(i) == movedPoints[j]){
                       needToMove = false;
                       break;
                   }
                }
                if (needToMove) {
                    movedPoints[j]->getSprite().move(28, 31);
                }
            }
            movedPoints.clear();
        }
    }
    void loadTexture(){
        background.loadFromFile("../img/background.png");
        windowTetris.loadFromFile("../img/frame.png");
        backgroundSprite.setTexture(background);
        windowTetrisSprite.setTexture(windowTetris);
    }
    virtual bool checkCollisonLRD(tetramino* figure) = 0;
};


#endif //TETRIS_GAMEFIELD_HPP
