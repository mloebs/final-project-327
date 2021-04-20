// This example demostrates the main loop
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

int main() {

  sf::RenderWindow window(sf::VideoMode(200, 200), "wcholden@bu.edu");
  sf::Event event;

  while (window.isOpen()) {
    sf::Event event;
    
while (window.pollEvent(event)) {
  if (event.type == sf::Event::Closed) {
    window.close();
  } else if (event.type == sf::Event::MouseButtonPressed) {
    std::cout << "Mouse button pressed" << std::endl;
  } else if (event.type == sf::Event::KeyPressed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      std::cout << "Space bar pressed" << std::endl;
    }
  }
}

}

  return 0;
}