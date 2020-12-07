#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include "gamefield.hpp"
#include "tetramino.hpp"

using namespace sf;


class game : public gamefield{
    const int delay = 500;
public:
    int startGame(){
        clockRotate.restart();
        clockMoveX.restart();
        instantFall.restart();
        clockMoveY.restart();
        RenderWindow window(sf::VideoMode(320, 480), "The Game!");
        window.setFramerateLimit(32);
        int dx = 0;
        bool dy = false;
        bool rotate = false;
        ZTetramino* current = new ZTetramino;
        curAndNextTetra[0] = current;
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (event.type == Event::KeyPressed){
                int oldCoord[4][2];
                if (event.key.code == Keyboard::Up){
                    if (clockRotate.getElapsedTime().asMilliseconds() > delay/4){
                        curAndNextTetra[0]->rotate(oldCoord);
                        if(!checkCollisonLRD(curAndNextTetra[0])){
                            curAndNextTetra[0]->backOldCoord(oldCoord);
                        }
                        checkCollisonLRD(curAndNextTetra[0]);
                        clockRotate.restart();
                    }
                } else if (event.key.code == Keyboard::Right){
                    if (clockMoveX.getElapsedTime().asMilliseconds() > delay/10){
                        curAndNextTetra[0]->moveLR(1,oldCoord);
                        if(!checkCollisonLRD(curAndNextTetra[0])){
                            curAndNextTetra[0]->backOldCoord(oldCoord);
                        }
                        clockMoveX.restart();
                    }
                } else if (event.key.code == Keyboard::Left){
                    if (clockMoveX.getElapsedTime().asMilliseconds() > delay/10) {
                        curAndNextTetra[0]->moveLR(-1,oldCoord);
                        if(!checkCollisonLRD(curAndNextTetra[0])){
                            curAndNextTetra[0]->backOldCoord(oldCoord);
                        }
                        clockMoveX.restart();
                    }
                } else if (event.key.code == Keyboard::Down){
                    if (clockMoveY.getElapsedTime().asMilliseconds() > delay/10) {
                        current[0].fallTetr(oldCoord);
                        if(!checkCollisonLRD(curAndNextTetra[0])){
                            curAndNextTetra[0]->backOldCoord(oldCoord);
                        }
                        clockMoveY.restart();
                    }
                }
            }
            if (instantFall.getElapsedTime().asMilliseconds() > delay){
                int oldCoord[4][2];
                curAndNextTetra[0]->fallTetr(oldCoord);
                if(!checkCollisonLRD(curAndNextTetra[0])){
                    curAndNextTetra[0]->backOldCoord(oldCoord);
                };
                instantFall.restart();
                clockMoveY.restart();
            }
            window.clear(Color::White);
            for (int i = 0; i < 4; ++i) {
                curAndNextTetra[0]->drawSprite(window);
            }
            window.display();
        }
    }
    bool checkCollisionInUp() override {
        return 1;
    }
    bool checkCollisonLRD(tetramino  *figure) override {
        for (int i = 0; i < 4 ; ++i) {
            if (curAndNextTetra[0]->getTetr(i)->getX() < 0 || curAndNextTetra[0]->getTetr(i)->getX() > W || curAndNextTetra[0]->getTetr(i)->getY() >= H){
                return 0;
            } else if (field[curAndNextTetra[0]->getTetr(i)->getY()][curAndNextTetra[0]->getTetr(i)->getX()]){
                return 0;
            }
        }
        return 1;
    }
};




#endif //TETRIS_GAME_HPP
