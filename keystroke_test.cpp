// This example demostrates the main loop
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <string>
using std::string;


int main() {

  sf::RenderWindow window(sf::VideoMode(1000, 1000), "wcholden@bu.edu");
  sf::Event event;
  sf::Text mytext;
  sf::Font font;

  int pos = 0;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  mytext.setFont(font);
  mytext.setPosition(pos, 20);
  mytext.setCharacterSize(30);
  mytext.setFillColor(sf::Color::White);
  char mychar;


  while (window.isOpen()) {
    sf::Event event;

    
while (window.pollEvent(event)) {
  if (event.type == sf::Event::Closed) {
    window.close();
  }
    else if (event.type == sf::Event::TextEntered)
{
    if (event.text.unicode < 128) {
        // std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
        mychar = event.text.unicode;

        string mystring(1, mychar);
        mytext.setString(mystring);
        std::cout << mystring << "\n";
        mytext.setPosition(pos, 20);
        pos += 20;
      }

}
}

//   } else if (event.type == sf::Event::MouseButtonPressed) {
//     std::cout << "Mouse button pressed" << std::endl;
//     window.draw(mytext);    
//   } else if (event.type == sf::Event::KeyPressed) {
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//       //std::cout << "Space bar pressed" << std::endl;
//       window.draw(mytext);
//     }
//   }
// }

window.draw(mytext);
window.display();

}
  return 0;
}