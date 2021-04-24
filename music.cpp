
// g++ music.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -Wall -o music
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using std::cin;
using std::cout;
using std::vector;
using std::string;

// reads in lyrics line by line from file, each line element in vector
// I guess could be run when game is started? 
// have a vector of all the song files and loop through to load each
vector<string> get_lyrics(string filename) { // eg "roxanne.txt"
  vector<string> lyrics;
  string line;
  std::ifstream lyricfile;
  lyricfile.open(filename);
  while (std::getline(lyricfile, line))
    lyrics.push_back(line);
  lyricfile.close();
  return lyrics;
}

string current_line_your_song(vector<string> lyrics, vector<int> intervals, int curr_sec) {
  if (curr_sec >= intervals.at(0) && curr_sec < intervals.at(1)) {
    return lyrics.at(0);
  } else {
    return "";
  }

}


int main() {   
  // clean this up later
  vector<string> roxanne_lyrics = get_lyrics("roxanne.txt");
  vector<string> cant_help_lyrics = get_lyrics("cant_help.txt");
  vector<string> buble_lyrics = get_lyrics("buble.txt");
  vector<string> nothing_lyrics = get_lyrics("nothing.txt");
  vector<string> your_song_lyrics = get_lyrics("your_song.txt");
  vector<int> roxanne_intervals {19, 22, 27, 29, 33, 36, 41, 44, 49, 52, 55, 59, 63, 67, 70, 73, 76, 91, 94, 98, 102, 106, 109, 113, 116, 120, 123, 127, 130, 134, 137, 141, 144, 148, 151, 154, 158, 162, 165, 169, 172, 175, 179, 182, 185};
  vector<int> cant_help_intervals {8, 14, 21, 36, 43, 50, 64, 68, 72, 76, 83, 90, 97, 111, 115, 119, 122, 129, 135, 143, 157, 174};
  vector<int> buble_intervals {19, 27, 35, 38, 50, 58, 65, 67, 78, 84, 93, 98, 106, 113, 121, 133, 161, 168, 175, 179, 183, 188, 202, 217};
  vector<int> nothing_intervals {40, 43, 47, 51, 56, 64, 65, 71, 74, 76, 83, 85, 90, 93, 96, 101, 114, 119, 123, 125, 132, 142, 145, 151, 157, 161, 164, 170, 173, 179, 182, 185, 192, 194, 201, 208, 213, 222};
  vector<int> your_song_intervals {8, 12, 15, 23, 30, 39, 44, 47, 54, 62, 72, 76, 79, 87, 89, 91, 95, 113, 120, 128, 131, 135, 145, 149, 153, 160, 168, 177, 181, 185, 192, 194, 196, 201, 211, 213, 215, 220, 229}; 


  sf::Music music;
  if (!music.openFromFile("your_song.ogg"))
   return -1; // error
  music.play();
  //sf::Time song_duration = music.getDuration();
  // cout << song_duration.asSeconds() << "\n";  //show total duration of song

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text shown_lyric;
  shown_lyric.setFont(font);
  shown_lyric.setCharacterSize(20);
  shown_lyric.setString("");
  shown_lyric.setFillColor(sf::Color::White);

  sf::RenderWindow window(sf::VideoMode(200, 200), "mloebs@bu.edu");
  window.setFramerateLimit(10);

  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          music.stop();
          window.close();
        }
        // while (music.getStatus() == 2)  // while playing
      }
      int curr_sec = floor(music.getPlayingOffset().asSeconds());


      string curr_lyric = current_line_your_song(your_song_lyrics, your_song_intervals, curr_sec);
      shown_lyric.setString(curr_lyric);

      cout << curr_sec << "\n";


      window.clear();
      window.draw(shown_lyric);
      window.display();
      
  }

  return 0;
}
