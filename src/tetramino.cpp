#include "tetramino.hpp"

 point::point() {
    texture.loadFromFile("../img/tiles.png");
    x = 0;
    y = 0;
}
point::point(int nx, int ny) : x(nx),y(ny){
    texture.loadFromFile("../img/tiles.png");
}

int point::getX() const {
    return x;
}

int point::getY() const {
    return y;
}

void point::setCoord(int x, int y) {
    this->x = x;
    this->y = y;
    sprite.setPosition((float)x * 18,(float)y * 18);
}

void point::setSprite(int color) {
    if (color < 1 || color > 8){
        color = 1;
    }
    sprite.setTexture(texture);
    if (color == 1){
        sprite.setTextureRect(sf::IntRect(0,0,18,18));
    } else{
        sprite.setTextureRect(sf::IntRect(18*color,0,18,18));
    }
}

sf::Sprite &point::getSprite() {
    return sprite;
}


void point::drawSprite(sf::RenderWindow &window) {
    sprite.setPosition((float)x*18 + 28,(float)y*18 + 31);
    window.draw(sprite);
}
void point::dropDown() {
    y += 1;
    sprite.setPosition((float)x*18 ,(float)y*18);
}

sf::Texture point::texture;



tetramino::tetramino(){
    for (int i = 0; i < 4; ++i) {
        tetr[i] = new point(0,0);
        tetr[i]->setSprite(1);
    }
}
void tetramino::moveLR(short turn, int oldCoord[][2]){
    for (int i = 0; i < 4; ++i) {
        oldCoord[i][0] = tetr[i]->getX();
        oldCoord[i][1] = tetr[i]->getY();
        tetr[i]->setCoord(tetr[i]->getX()+(int)turn, tetr[i]->getY());
    }

}
void tetramino::fallTetr(int oldCoord[][2]){
    for (int i = 0; i < 4; ++i) {
        oldCoord[i][0] = tetr[i]->getX();
        oldCoord[i][1] = tetr[i]->getY();
        tetr[i]->setCoord(tetr[i]->getX(),tetr[i]->getY()+1);
    }
}

void tetramino::rotate(int oldCoord[][2]){
    point* center = tetr[1];
    for (int i = 0; i < 4 ; ++i) {
        oldCoord[i][0] = tetr[i]->getX();
        oldCoord[i][1] = tetr[i]->getY();
        int x = tetr[i]->getY() - center->getY();
        int y = tetr[i]->getX() - center->getX();
        tetr[i]->setCoord(center->getX() - x,center->getY()+y);
    }
}

point* tetramino::getTetr(int number){
    if (number > 3 || number < 0){
        return tetr[0];
    }
    return tetr[number];
}


void tetramino::drawSprite(sf::RenderWindow& window){
    for (auto & i : tetr) {
        window.draw(i->getSprite());
    }
}
void tetramino::backOldCoord(int coords[][2]){
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(coords[i][0],coords[i][1]);
    }
}


void ITetramino::setColor(){}
void ITetramino::setPos(){
    position[0] = 1;
    position[1] = 3;
    position[2] = 5;
    position[3] = 7;
}
ITetramino::ITetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}

oTetramino::oTetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}

void oTetramino::rotate(int oldCoord[][2]){
    for (int i = 0; i < 4 ; ++i) {
        oldCoord[i][0] = tetr[i]->getX();
        oldCoord[i][1] = tetr[i]->getY();
    }
}
void oTetramino::setColor() {
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setSprite(2);
    }
}
void oTetramino::setPos() {
    position[0] = 2;
    position[1] = 3;
    position[2] = 4;
    position[3] = 5;
}



sTetramino::sTetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}
void sTetramino::setColor(){
    for (auto & i : tetr) {
        i->setSprite(3);
    }
}
void sTetramino::setPos() {
    position[0] = 2;
    position[1] = 4;
    position[2] = 5;
    position[3] = 7;
}


ZTetramino::ZTetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}
void ZTetramino::setColor()  {
    for (auto & i : tetr) {
        i->setSprite(4);
    }
}
void ZTetramino::setPos()  {
    position[0] = 3;
    position[1] = 5;
    position[2] = 4;
    position[3] = 6;
}

LTetramino::LTetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}
void LTetramino::setColor()  {
    for (auto & i : tetr) {
        i->setSprite(5);
    }
}
void LTetramino::setPos()  {
    position[0] = 2;
    position[1] = 3;
    position[2] = 5;
    position[3] = 7;
}


JTetramino::JTetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}
void JTetramino::setColor() {
    for (auto & i : tetr) {
        i->setSprite(6);
    }
}
void JTetramino::setPos()  {
    position[0] = 3;
    position[1] = 5;
    position[2] = 7;
    position[3] = 6;
}


tTetramino::tTetramino() :tetramino(){
    setColor();
    setPos();
    for (int i = 0; i < 4; ++i) {
        tetr[i]->setCoord(position[i] % 2 ,position[i] / 2);
    }
}
void tTetramino::setColor() {
    for (auto & i : tetr) {
        i->setSprite(7);
    }
}
void tTetramino::setPos() {
    position[0] = 3;
    position[1] = 5;
    position[2] = 4;
    position[3] = 7;
}

