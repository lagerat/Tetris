#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include "gamefield.hpp"
#include "tetramino.hpp"

using namespace sf;

class game : public gamefield{
public:
    int startGame(){
        RenderWindow window(sf::VideoMode(320, 480), "The Game!");
        window.setFramerateLimit(32);
        int dx = 0;
        bool dy = false;
        bool rotate = false;
        ITetramino* current = new ITetramino;
        curAndNextTetra.push_back(current);
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Up){
                    rotate = true;
                } else if (event.key.code == Keyboard::Right){
                    dx = 1;
                } else if (event.key.code == Keyboard::Left){
                    dx = -1;
                } else if (event.key.code == Keyboard::Down){
                    dy = true;
                }
            }
            window.clear(Color::White);
            for (int i = 0; i < 4; ++i) {
                current->drawSprite(window);
            }
            window.display();
        }
    }
    void checkCollisionInUp() override {
        return;
    }
};



//if (rotate && clockRotate.getElapsedTime().asMilliseconds() > 100){
//point center = tetramino[1];
//for (int i = 0; i < 4 ; ++i) {
//int x = tetramino[i].getY() - center.getY();
//int y = tetramino[i].getX() - center.getX();
//tetramino[i].setCoord(center.getX() - x,center.getY()+y);
//}
//clockRotate.restart();
//}
//
//if (dx != 0 && clockMoveX.getElapsedTime().asMilliseconds() > 50 ){
//for (int i = 0; i < 4; ++i) {
//tetramino[i].setCoord(tetramino[i].getX()+dx, tetramino[i].getY());
//}
//clockMoveX.restart();
//}
//if (dy && clockMoveY.getElapsedTime().asMilliseconds() > 50){
//for (int i = 0; i < 4; ++i) {
//tetramino[i].setCoord(tetramino[i].getX(),tetramino[i].getY()+1);
//}
//clockMoveY.restart();
//instantFall.restart();
//}
//if (instantFall.getElapsedTime().asMilliseconds() > 500){
//for (int i = 0; i < 4; ++i) {
//tetramino[i].setCoord(tetramino[i].getX(),tetramino[i].getY()+1);
//}
//instantFall.restart();
//}

#endif //TETRIS_GAME_HPP
