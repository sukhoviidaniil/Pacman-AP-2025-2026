//
// Created by Kaede on 2025-10-23.
//

#include <SFML/Graphics.hpp>

int main(){
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CMake SFML Project");
    window.setFramerateLimit(30);
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        window.clear();
        window.display();
    }
}