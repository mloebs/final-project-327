// This example demostrates the main loop
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
int main(int argc, char ** argv) {
  sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");
  sf::Event event;
  // A Clock starts counting as soon as it's created
  sf::Color color(sf::Color::Red);
  // C++ 11 way of generating a random between 0 - 255
  // mt19937 is an implementation of the Mersenne Twister pseudo random number generator
  // random_device() returns a random number to use as a seed for the mt algorithm... slow however so that's why we dont just use it for all randoms if you were wondering
  // mt results arent in a human friendly format, so we use uniform_int_distribution to "shape" the results to our range and type
  // uniform_int_distribution is a fairly "light" object.  random_device and mt19937 aren't.
  std::uniform_int_distribution<int> randomColorRange(0, 255);
  std::random_device rd;
  std::mt19937 randomNumbers(rd());
  
  // Pre-C++ 11 but more common way (*with issues, see:
  //https://www.reddit.com/r/programming/comments/1rnudl/quite_interesting_why_cs_rand_is_considered/
  // Mostly doesn't apply to game devs if not using rand for say... security.
  
  /*
  srand(time(NULL));          //seed random number generator with the current time
  auto randomNumber = rand() % 255;   //generate a random number then confine it to a value of 0 - 255.
  */
  while (renderWindow.isOpen()){
    // Check for all the events that occured since the last frame.
    while (renderWindow.pollEvent(event)){
      //Handle events here
      if (event.type == sf::Event::EventType::Closed)
        renderWindow.close();
      //Respond to key pressed events
      if (event.type == sf::Event::EventType::KeyPressed){
        if (event.key.code == sf::Keyboard::Space){
          color.r = randomColorRange(randomNumbers);
        }
      }
    }
                      
    // Now demonstrate input via polling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        color.r = 0;
      else
        color.r = randomColorRange(randomNumbers);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        color.g = 0;
      else
        color.g = randomColorRange(randomNumbers);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        color.b = 0;
      else
        color.b = randomColorRange(randomNumbers);
    
    renderWindow.clear(color);
    renderWindow.display();
  }
}