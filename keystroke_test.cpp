// Copyright Will Holden wcholden@bu.edu
// This example demostrates the main loop
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include<vector>
using std::string;
using std::ifstream;
using std::getline;
using std::cout;
using std::vector;


int main() {

  sf::RenderWindow window(sf::VideoMode(720, 720), "wcholden@bu.edu");
  sf::Event event;
  sf::Text mylyrics;
  sf::Text mytext;
  sf::Font font;

  float pos = 0.0;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  mylyrics.setFont(font);
  mytext.setFont(font);
  mylyrics.setPosition(20, 20);
  mytext.setPosition(pos, 200);
  mylyrics.setCharacterSize(30);
  mytext.setCharacterSize(30);
  mylyrics.setFillColor(sf::Color::White);
  mytext.setFillColor(sf::Color::White);
  char mychar;
  vector<string> lyrics;
  string line;
  string current_line;
  int i = 0; // iterate through lines in lyrics
  int j = 0; // iterate through characters in lines
  int mistakes = 0; // counts mistakenly typed chars
  bool line_switch = false; // indicates to switch lines
  float char_width;

  ifstream infile("thefile.txt");
  while(getline(infile, line)) {
    lyrics.push_back(line);
  }
  current_line = lyrics[0];

  // Window animation
  while (window.isOpen()) {
    sf::Event event;
    mylyrics.setString(lyrics[i]);

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } 

    // Proceed to next line of lyrics
    if (line_switch == true) {
      current_line = lyrics[i];
      i += 1;
      j = 0;
      line_switch = false;
    }

      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
          mychar = event.text.unicode;

          // if the character typed is correct
          if (mychar == current_line[j]) {
            mytext.setString(mychar);
            char_width = mytext.getLocalBounds().width;
            mytext.setPosition(pos, 200);
            j += 1; 
            pos += char_width;
          }

          // if the character typed is NOT correct
          else {
            mistakes += 1;
          }

          
        }
      }
    }

    window.draw(mylyrics);
    window.draw(mytext);
    window.display();

  }

  cout << mistakes << "\n";
  return 0;
}