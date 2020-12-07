#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include "gamefield.hpp"
#include "tetramino.hpp"
#include <ctime>

using namespace sf;


class game : public gamefield{
    const int delay = 500;
    bool tetraminoIsCreated = true;
    bool tetraminoIsStoped = false;
    tetramino* current;
public:
    int startGame(){
        srand(time(NULL));
        clockRotate.restart();
        clockMoveX.restart();
        instantFall.restart();
        clockMoveY.restart();
        pointsOnField.reserve(W*H);
        RenderWindow window(sf::VideoMode(320, 480), "Tetris");
        window.setFramerateLimit(32);
        current = new oTetramino;
        while (window.isOpen())
        {
            if (!tetraminoIsCreated){
//                switch (randTypeOfTetramino()) {
                switch (2) {
                    case 1:
                        current = new ITetramino;
                        break;
                    case 2:
                        current = new oTetramino;
                        break;
                    case 3:
                        current = new sTetramino;
                        break;
                    case 4:
                        current = new ZTetramino;
                        break;
                    case 5:
                        current = new LTetramino;
                        break;
                    case 6:
                        current = new JTetramino;
                        break;
                    case 7:
                        current = new tTetramino;
                        break;
                }
                tetraminoIsCreated = true;
            }
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Up){
                    if (clockRotate.getElapsedTime().asMilliseconds() > delay/4){
                        int oldCoord[4][2];
                        current->rotate(oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockRotate.restart();
                    }
                } else if (event.key.code == Keyboard::Right){
                    if (clockMoveX.getElapsedTime().asMilliseconds() > delay/10){
                        int oldCoord[4][2];
                        current->moveLR(1,oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockMoveX.restart();
                    }
                } else if (event.key.code == Keyboard::Left){
                    int oldCoord[4][2];
                    if (clockMoveX.getElapsedTime().asMilliseconds() > delay/10) {
                        current->moveLR(-1,oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockMoveX.restart();
                    }
                } else if (event.key.code == Keyboard::Down){
                    int oldCoord[4][2];
                    if (clockMoveY.getElapsedTime().asMilliseconds() > delay/10) {
                        current[0].fallTetr(oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockMoveY.restart();
                    }
                }
            }
            if (instantFall.getElapsedTime().asMilliseconds() > delay){
                int oldCoord[4][2];
                current->fallTetr(oldCoord);
                if(!checkCollisonLRD(current)){
                    current->backOldCoord(oldCoord);
                    for (int i = 0; i < 4; ++i) {
                        int ny = current->getTetr(i)->getY();
                        int nx = current->getTetr(i)->getX();
                        field[ny][nx] = 1;
                    }
                    insertToVector(current);
                    delete current;
                    checkAndDelLines();
                    tetraminoIsCreated = false;
                }
                instantFall.restart();
                clockMoveY.restart();
            }
            window.clear(Color::White);
            if (tetraminoIsCreated) {
                for (int i = 0; i < 4; ++i) {
                    current->drawSprite(window);
                }
            }
            for (auto & i : pointsOnField) {
                i->drawSprite(window);
            }
            window.display();
        }
        return 0;
    }
    bool checkCollisionInUp() override {
        return true;
    }
    bool checkCollisonLRD(tetramino  *figure) override {
        for (int i = 0; i < 4 ; ++i) {
            if (figure->getTetr(i)->getX() < 0 || figure->getTetr(i)->getX() >= W || figure->getTetr(i)->getY() >= H){
                return false;
            } else if (field[figure->getTetr(i)->getY()][figure->getTetr(i)->getX()]){
                return false;
            }
        }
        return true;
    }
    void insertToVector(tetramino* cur){
        for (int i = 0; i < 4; ++i) {
            pointsOnField.push_back(cur->getTetr(i));
        }
    }
    static inline int randTypeOfTetramino(){
         return rand() % 6 + 1;
    }
};




#endif //TETRIS_GAME_HPP
