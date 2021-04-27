// Copyright Joshua Singh
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
  lyrics.push_back(" ");
  lyricfile.close();
  return lyrics;
}


int main() {

  int selection = 4;

  vector<string> roxanne_lyrics = get_lyrics("roxanne.txt");
  vector<string> cant_help_lyrics = get_lyrics("cant_help.txt");
  vector<string> buble_lyrics = get_lyrics("buble.txt");
  vector<string> nothing_lyrics = get_lyrics("nothing.txt");
  vector<string> your_song_lyrics = get_lyrics("your_song.txt");
  vector<int> roxanne_intervals {19, 22, 27, 29, 33, 36, 41, 44, 49, 52, 55, 59, 63, 67, 70, 73, 76, 91, 94, 98, 102, 106, 109, 113, 116, 120, 123, 127, 130, 134, 137, 141, 144, 148, 151, 154, 158, 162, 165, 169, 172, 175, 179, 182, 185, 190}; //190
  vector<int> cant_help_intervals {8, 14, 21, 36, 43, 50, 64, 68, 72, 76, 83, 90, 97, 111, 115, 119, 122, 129, 135, 143, 157, 174, 181}; //181
  vector<int> buble_intervals {19, 27, 35, 38, 50, 58, 65, 67, 78, 84, 93, 98, 106, 113, 121, 133, 161, 168, 175, 179, 183, 188, 202, 217, 233}; //233
  vector<int> nothing_intervals {40, 43, 47, 52, 58, 64, 68, 71, 74, 77, 81, 86, 90, 93, 96, 101, 114, 119, 122, 125, 131, 138, 142, 145, 151, 157, 160, 164, 166, 170, 173, 179, 181, 185, 193, 195, 202, 207, 214, 294}; //294
  vector<int> your_song_intervals {8, 12, 15, 23, 30, 39, 44, 47, 54, 62, 72, 76, 79, 87, 89, 91, 95, 113, 120, 128, 131, 135, 145, 149, 153, 160, 168, 177, 181, 185, 192, 194, 196, 201, 211, 213, 215, 220, 244}; //244

  sf::RenderWindow window(sf::VideoMode(720, 720), "JBC Hero");
  sf::Text mylyrics;
  sf::Text mytext;
  sf::Text mypreview;
  sf::Font font;
  sf::Time song_duration;
  sf::Music music;

  sf::Color Gray(100, 100, 100);

  float pos = 0.0;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  // Properties of text
  mylyrics.setFont(font);
  mytext.setFont(font);
  mypreview.setFont(font);
  mylyrics.setPosition(20, 50);
  mytext.setPosition(pos, 200);
  mypreview.setPosition(20, 20);
  mylyrics.setCharacterSize(22);
  mytext.setCharacterSize(22);
  mypreview.setCharacterSize(16);
  mylyrics.setFillColor(sf::Color::White);
  mytext.setFillColor(sf::Color::White);
  mypreview.setFillColor(Gray);


  // variables
  char mychar;                           // character typed by user
  vector<char> michar;
  vector<char> current_char;
  vector<string> lyrics = buble_lyrics;


  int ending;
  string line;
  string current_line;
  int i = 0;                               // iterate through lines in lyrics
  int j = 0;                               // iterate through characters in lines
  float mistakes = 0;
  int missing = 0;                      // counts mistakenly typed chars
  float char_width;
  vector<int> intervals;

  float char_correct = 0;          // correctly entered chars
  float char_total = 0;              // total entered chars
  float char_nothing = 0;             // count if user doesn't enter anything

  // song selection

  if (selection == 0) {
    lyrics = roxanne_lyrics;
    intervals = roxanne_intervals;
    if (!music.openFromFile("roxanne.ogg"))
      return -1; // error
    music.play();
  }

  else if (selection == 1) {
    lyrics = your_song_lyrics;
    intervals = your_song_intervals;
    if (!music.openFromFile("your_song.ogg"))
      return -1; // error
    music.play();
  }

  else if (selection == 2) {
    lyrics = cant_help_lyrics;
    intervals = cant_help_intervals;
    if (!music.openFromFile("cant_help.ogg"))
      return -1; // error
    music.play();
  }

  else if (selection == 3) {
    lyrics = nothing_lyrics;
    intervals = nothing_intervals;
    if (!music.openFromFile("nothing.ogg"))
      return -1; // error
    music.play();
  }

  else if (selection == 4) {
    lyrics = buble_lyrics;
    intervals = buble_intervals;
    if (!music.openFromFile("buble.ogg"))
      return -1; // error
    music.play();
  }

  song_duration = music.getDuration();
  ending = ceil(song_duration.asSeconds());

  // Window animation
  while (window.isOpen()) {
    sf::Event event;
    mylyrics.setString(lyrics.at(i));

    // Current second in song
    int curr_sec = floor(music.getPlayingOffset().asSeconds());

    if (i < lyrics.size()) {
      if (i < (lyrics.size() - 1)) {
        mypreview.setString(lyrics.at((i + 1)));
      }

      // Switching line
      if (curr_sec >= intervals.at(i)) {
        current_line = lyrics.at(i);
        for (char c :current_line){
          current_char.push_back(c);
        }
        i += 1;
        j = 0;
        pos = 20.0;
        window.clear();
        mytext.setString(" ");
        window.draw(mylyrics);
        window.draw(mypreview);
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
                char_correct++;
                char_total++;
                michar.push_back(mychar);
              }
             

              // if the character typed is NOT correct
              else {
                mistakes += 1;
                char_total++;
                michar.push_back(mychar);
              }
            }
          }
        }
      }
      window.draw(mytext);
      window.display();
    }

    if (curr_sec == (ending - 1)) {
      window.close();
    }
  }


  // Accuracy calc
  float accuracy;
  // Get lyric lines in charachters
  vector<char> char_lyrics;
  for (string s : lyrics) {
    for (char c : s)
      if (c != ' ') {
        char_lyrics.push_back(c);
      }
  }
  float char_lyrics_size = char_lyrics.size();

  // count how many chars users missed
  float current_char_size = current_char.size();
  char_nothing = current_char_size - char_total;



  // if no entered chars accuracy = 0
  if (char_total == 0) {
    accuracy = 0;
  } else {
    accuracy = ( (char_correct-mistakes-char_nothing) / (current_char_size) * 100);
  }


  cout << "accuracy:" << accuracy << "\n";
  return 0;
}


