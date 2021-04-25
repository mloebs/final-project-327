// Copyright Will Holden wcholden@bu.edu
// This example demostrates the main loop
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include<vector>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cctype>
#include <algorithm>
using std::string;
using std::ifstream;
using std::getline;
using std::cout;
using std::vector;


vector<string> get_lyrics(string filename) { // eg "roxanne.txt"
  vector<string> lyrics;
  string line;
  std::ifstream lyricfile;
  lyricfile.open(filename);
  while (std::getline(lyricfile, line)) {
    std::transform(line.begin(), line.end(), line.begin(), ::toupper);
    lyrics.push_back(line);
  }
  lyrics.push_back(" ");
  lyricfile.close();
  return lyrics;
}


int main() {

  vector<string> roxanne_lyrics = get_lyrics("roxanne.txt");
  vector<string> cant_help_lyrics = get_lyrics("cant_help.txt");
  vector<string> buble_lyrics = get_lyrics("buble.txt");
  vector<string> nothing_lyrics = get_lyrics("nothing.txt");
  vector<string> your_song_lyrics = get_lyrics("your_song.txt");
  vector<int> roxanne_intervals {19, 22, 27, 29, 33, 36, 41, 44, 49, 52, 55, 59, 63, 67, 70, 73, 76, 91, 94, 98, 102, 106, 109, 113, 116, 120, 123, 127, 130, 134, 137, 141, 144, 148, 151, 154, 158, 162, 165, 169, 172, 175, 179, 182, 185, 190};
  vector<int> cant_help_intervals {8, 14, 21, 36, 43, 50, 64, 68, 72, 76, 83, 90, 97, 111, 115, 119, 122, 129, 135, 143, 157, 174};
  vector<int> buble_intervals {19, 27, 35, 38, 50, 58, 65, 67, 78, 84, 93, 98, 106, 113, 121, 133, 161, 168, 175, 179, 183, 188, 202, 217};
  vector<int> nothing_intervals {40, 43, 47, 51, 56, 64, 65, 71, 74, 76, 83, 85, 90, 93, 96, 101, 114, 119, 123, 125, 132, 142, 145, 151, 157, 161, 164, 170, 173, 179, 182, 185, 192, 194, 201, 208, 213, 222};
  vector<int> your_song_intervals {8, 12, 15, 23, 30, 39, 44, 47, 54, 62, 72, 76, 79, 87, 89, 91, 95, 113, 120, 128, 131, 135, 145, 149, 153, 160, 168, 177, 181, 185, 192, 194, 196, 201, 211, 213, 215, 220, 244}; // 229

  sf::RenderWindow window(sf::VideoMode(720, 720), "wcholden@bu.edu");
  sf::Text mylyrics;
  sf::Text mytext;
  sf::Font font;

  float pos = 0.0;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");


  // Properties of text
  mylyrics.setFont(font);
  mytext.setFont(font);
  mylyrics.setPosition(20, 20);
  mytext.setPosition(pos, 200);
  mylyrics.setCharacterSize(22);
  mytext.setCharacterSize(22);
  mylyrics.setFillColor(sf::Color::White);
  mytext.setFillColor(sf::Color::White);


  // Find number of chars in song lyrics
  char mychar;
  vector<string> lyrics = roxanne_lyrics;

  vector<char> char_lyrics;
  for (string s: lyrics) {
    for (char c :s)
      if (c != ' ') {
    char_lyrics.push_back(c);
  }
  }

  int char_lyrics_size = char_lyrics.size();

  // Create accuracy 
  float accuracy;


  string line;
  string current_line;
  string current_caps;
  int i = 0; // iterate through lines in lyrics
  int j = 0; // iterate through characters in lines
  float mistakes = 0; // counts mistakenly typed chars
  float char_width;


  // Play music from .ogg files
  sf::Music music;
  if (!music.openFromFile("roxanne.ogg"))
    return -1; // error
  music.play();

  // Window animation
  while (window.isOpen()) {
    sf::Event event;
    mylyrics.setString(lyrics.at(i));
    // while (music.getStatus() == 2)  // while playing

    // Current second in song
    int curr_sec = floor(music.getPlayingOffset().asSeconds());


    // Switching line
    if (curr_sec >= roxanne_intervals.at(i)) {
      current_line = lyrics.at(i);
      cout << curr_sec << " : " << roxanne_intervals.at(i) << "\n";
      i += 1;
      j = 0;
      pos = 20.0;
      window.clear();
      mytext.setString(" ");
      window.draw(mylyrics);
    }

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        music.stop();
      }


      // Proceed to next line of lyrics
      if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
          mychar = toupper(event.text.unicode);


          if (j < current_line.length()) {

            // if the character typed is correct
            if (mychar == current_line.at(j)) {
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
    }

    window.draw(mytext);
    window.display();

  }
  sf::Time song_duration = music.getDuration();
  //cout << ceil(song_duration.asSeconds()) << "\n";  //show total duration of song
 

  // Create accuracy and cout accuracy
  accuracy = (mistakes/char_lyrics_size) *100;
  cout << "Accuracy: " << accuracy << "\n";
  
  return 0;
}
