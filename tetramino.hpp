#ifndef TETRIS_TETRAMINO_HPP
#define TETRIS_TETRAMINO_HPP

#include <iostream>


class point{
private:
    int x;
    int y;
    sf::Sprite sprite;
public:
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
        sprite.setTextureRect(sf::IntRect(0,0,18*color,18*color));
    }
    sf::Sprite getSprite(){
        return sprite;
    }
     virtual void drawSprite(sf::RenderWindow& window){
        window.draw(sprite);
    }
};

sf::Texture point::texture;

//const int figures[7][4] = {
//        1,3,5,7, // I
//        2,4,5,7, // Z
//        3,5,4,6, // S
//        3,5,4,7, // T
//        2,3,5,7, // L
//        3,5,7,6, // J
//        2,3,4,5, // O
//};



class tetramino : public point{
protected:
    int position[4];
    point* tetr[4];
public:
    tetramino(){
        for (int i = 0; i < 4; ++i) {
            tetr[i] = new point(0,0);
            tetr[i]->setSprite(1);
        }
    }
//    tetramino(int width = 0, int height = 0){
//        for (int i = 0; i < 4; ++i) {
//            tetr[i] = new point(width/2,height/2);
//        }
//    }
    void moveLR(bool turn){
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(tetr[i]->getX()+(int)turn, tetr[i]->getY());
        }
    }
    void fallTetr(){
        for (int i = 0; i < 4; ++i) {
            tetr[i]->setCoord(tetr[i]->getX(),tetr[i]->getY()+1);
        }
    }
    void drawSprite(sf::RenderWindow& window) override {
        for (int i = 0; i < 4; ++i) {
            window.draw(tetr[i]->getSprite());
            sf::Vector2f v(tetr[i]->getSprite().getPosition());
            std::cout  << "";
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
