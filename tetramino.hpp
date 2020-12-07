#ifndef TETRIS_TETRAMINO_HPP
#define TETRIS_TETRAMINO_HPP

#include <iostream>

class point{
private:
    int x;
    int y;
    sf::Sprite sprite;
public:
    bool isMoved = false;
    static sf::Texture texture;
    point(){
        texture.loadFromFile("../img/tiles.png");
        x = 0;
        y = 0;
    }
    point(int nx, int ny): x(nx),y(ny){
        texture.loadFromFile("../img/tiles.png");
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void setCoord(int x, int y){
        this->x = x;
        this->y = y;
        sprite.setPosition((float)x * 18,(float)y * 18);
    }
    void setSprite(int color = 1){
        if (color < 1 || color > 8){
            throw "error with color of tetramino";
        }
        sprite.setTexture(texture);
        if (color == 1){
            sprite.setTextureRect(sf::IntRect(0,0,18,18));
        } else{
            sprite.setTextureRect(sf::IntRect(18*color,0,18,18));
        }
    }
    void dropDown(){
        y += 1;
        sprite.setPosition((float)x*18,(float)y*18);
    }
    sf::Sprite& getSprite(){
        return sprite;
    }
     virtual void drawSprite(sf::RenderWindow& window){
        window.draw(sprite);
    }
};

sf::Texture point::texture;


class tetramino : public point{
protected:
    int position[4] = {1,3,5,7};
    point* tetr[4];
public:
    tetramino(){
        for (int i = 0; i < 4; ++i) {
            tetr[i] = new point(0,0);
            tetr[i]->setSprite(1);
        }
    }
    void moveLR(short turn, int oldCoord[][2]){

        for (int i = 0; i < 4; ++i) {
            oldCoord[i][0] = tetr[i]->getX();
            oldCoord[i][1] = tetr[i]->getY();
            tetr[i]->setCoord(tetr[i]->getX()+(int)turn, tetr[i]->getY());
        }

    }
    void fallTetr(int oldCoord[][2]){
        for (int i = 0; i < 4; ++i) {
            oldCoord[i][0] = tetr[i]->getX();
            oldCoord[i][1] = tetr[i]->getY();
            tetr[i]->setCoord(tetr[i]->getX(),tetr[i]->getY()+1);
        }
    }

    virtual void rotate(int oldCoord[][2]){
        point* center = tetr[1];
        for (int i = 0; i < 4 ; ++i) {
            oldCoord[i][0] = tetr[i]->getX();
            oldCoord[i][1] = tetr[i]->getY();
            int x = tetr[i]->getY() - center->getY();
            int y = tetr[i]->getX() - center->getX();
            tetr[i]->setCoord(center->getX() - x,center->getY()+y);
        }
    }

    point* getTetr(int number){
        if (number > 3 || number < 0){
            throw "GetTetr error, invalid data";
        }
        return tetr[number];
    }


    void drawSprite(sf::RenderWindow& window) override {
        for (int i = 0; i < 4; ++i) {
            window.draw(tetr[i]->getSprite());
        }
    }
    void backOldCoord(int coords[][2]){
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(coords[i][0],coords[i][1]);
        }
    }
    virtual void setColor(){
    }
    virtual void setPos(){}
};

class ITetramino : public tetramino{
public:
    void setColor() override {
    }
    void setPos() override {
        position[0] = 1;
        position[1] = 3;
        position[2] = 5;
        position[3] = 7;
    }
    ITetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }
};
class oTetramino : public tetramino{
public:
    oTetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }

    void rotate(int oldCoord[][2]) override {
        for (int i = 0; i < 4 ; ++i) {
            oldCoord[i][0] = tetr[i]->getX();
            oldCoord[i][1] = tetr[i]->getY();
        }
    }
    void setColor() override {
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setSprite(2);
        }
    }
    void setPos() override {
        position[0] = 2;
        position[1] = 3;
        position[2] = 4;
        position[3] = 5;
    }
};
class sTetramino : public tetramino{
public:
    sTetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }
    void setColor() override {
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setSprite(3);
        }
    }
    void setPos() override {
        position[0] = 2;
        position[1] = 4;
        position[2] = 5;
        position[3] = 7;
    }
};
class ZTetramino : public tetramino{
public:
    ZTetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }
    void setColor() override {
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setSprite(4);
        }
    }
    void setPos() override {
        position[0] = 3;
        position[1] = 5;
        position[2] = 4;
        position[3] = 6;
    }
};
class LTetramino : public tetramino{
public:
    LTetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }
    void setColor() override {
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setSprite(5);
        }
    }
    void setPos() override {
        position[0] = 2;
        position[1] = 3;
        position[2] = 5;
        position[3] = 7;
    }
};
class JTetramino : public tetramino{
public:
    JTetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }
    void setColor() override {
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setSprite(6);
        }
    }
    void setPos() override {
        position[0] = 3;
        position[1] = 5;
        position[2] = 7;
        position[3] = 6;
    }
};
class tTetramino : public tetramino{
public:
    tTetramino() :tetramino(){
        setColor();
        setPos();
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
        }
    }
    void setColor() override {
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setSprite(7);
        }
    }
    void setPos() override {
        position[0] = 3;
        position[1] = 5;
        position[2] = 4;
        position[3] = 7;
    }
};

#endif //TETRIS_TETRAMINO_HPP
