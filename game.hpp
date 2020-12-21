#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include "gamefield.hpp"
#include "tetramino.hpp"
#include <ctime>

using namespace sf;


class game : public gamefield{
    const int delay = 500;
    bool tetraminoIsCreated = false;
    tetramino* current;
    int gameMenu(sf::RenderWindow& window){
        Texture menuStart, menuEnd;
        menuStart.loadFromFile("../img/start.png");
        menuEnd.loadFromFile("../img/end.png");
        Sprite menu1(menuStart), menu2(menuEnd);
        menu1.setPosition(-120,50);
        menu2.setPosition(-130,150);
        int menuChoose = 0;
        window.setFramerateLimit(16);
        while (window.isOpen()){
            menuChoose = 0;
            menu1.setColor(Color::White);
            menu2.setColor(Color::White);
            if (IntRect(60,150,215,60).contains(Mouse::getPosition(window))){
            menu1.setColor(Color::Yellow);
            menuChoose = 1;
            }
            if (IntRect(80,250,180,60).contains(Mouse::getPosition(window))){
                menu2.setColor(Color::Blue);
                menuChoose = 2;
            }
            if (Mouse::isButtonPressed(Mouse::Left)){
                if (menuChoose == 2){
                    window.close();
                }
                if (menuChoose == 1){
                    return 1;
                }
            }
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color::Black);
            window.draw(menu1);
            window.draw(menu2);
            window.display();
        }
    }
public:
    int startGame(){
        srand(time(NULL));
        clockRotate.restart();
        clockMoveX.restart();
        instantFall.restart();
        clockMoveY.restart();
        pointsOnField.reserve(W*H);
        RenderWindow window(sf::VideoMode(320, 480), "Tetris");
        gameMenu(window);
        window.setFramerateLimit(32);
        loadTexture();
        while (window.isOpen())
        {

            if (!tetraminoIsCreated){
                switch (randTypeOfTetramino()) {
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
                if (!checkCollisonLRD(current)){
                    window.close();
                }
                for (int i = 0; i < 4; ++i) {
                    current->getTetr(i)->getSprite().move(28,31);
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
                        for (int i = 0; i < 4; ++i) {
                            current->getTetr(i)->getSprite().move(28,31);
                        }
                    }
                } else if (event.key.code == Keyboard::Right){
                    if (clockMoveX.getElapsedTime().asMilliseconds() > delay/10){
                        int oldCoord[4][2];
                        current->moveLR(1,oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockMoveX.restart();
                        for (int i = 0; i < 4; ++i) {
                            current->getTetr(i)->getSprite().move(28,31);
                        }
                    }
                } else if (event.key.code == Keyboard::Left){
                    int oldCoord[4][2];
                    if (clockMoveX.getElapsedTime().asMilliseconds() > delay/10) {
                        current->moveLR(-1,oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockMoveX.restart();
                        for (int i = 0; i < 4; ++i) {
                            current->getTetr(i)->getSprite().move(28,31);
                        }
                    }
                } else if (event.key.code == Keyboard::Down){
                    int oldCoord[4][2];
                    if (clockMoveY.getElapsedTime().asMilliseconds() > delay/10) {
                        current[0].fallTetr(oldCoord);
                        if(!checkCollisonLRD(current)){
                            current->backOldCoord(oldCoord);
                        }
                        clockMoveY.restart();
                        for (int i = 0; i < 4; ++i) {
                            current->getTetr(i)->getSprite().move(28,31);
                        }
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
                    checkAndDelLines(current);
                    delete current;
                    tetraminoIsCreated = false;
                }
                instantFall.restart();
                clockMoveY.restart();
                    for (int i = 0; i < 4; ++i) {
                        current->getTetr(i)->getSprite().move(28, 31);
                    }
            }
            window.clear(Color::White);
            window.draw(backgroundSprite);
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
