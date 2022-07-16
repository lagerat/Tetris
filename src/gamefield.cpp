#include "gamefield.hpp"

void gamefield::checkAndDelLines(tetramino *&current) {
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
                                (*it)->isMoved = true;
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
    if (!movedPoints.empty()){
        for (auto & movedPoint : movedPoints) {
            bool needToMove = true;
            for (int i = 0; i < 4; ++i) {
                if ( current->getTetr(i) == movedPoint){
                    needToMove = false;
                    break;
                }
            }
            if (needToMove) {
                if (movedPoint->isMoved) {
                    movedPoint->getSprite().move(28, 31);
                    movedPoint->isMoved = false;
                }
            }
        }
        movedPoints.clear();
    }
}

void gamefield::loadTexture() {
    background.loadFromFile("../img/background.png");
    windowTetris.loadFromFile("../img/frame.png");
    backgroundSprite.setTexture(background);
    windowTetrisSprite.setTexture(windowTetris);
}

