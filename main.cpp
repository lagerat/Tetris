#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Points");
    window.setFramerateLimit(120);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        sf::CircleShape circle;
        circle.setRadius(10.f);
        circle.setFillColor(sf::Color(255,255,200));
        window.draw(circle);
        window.display();
    }
}