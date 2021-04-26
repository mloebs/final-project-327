// Team 12: Type 2 Learn
// Summary:

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::vector;
using std::string;
using std::stoi;
using std::to_string;

/////////////////// Button Class ///////////////////
class Button{
public:
  Button(string name, int posx, int posy);
  void showButton(sf::RenderWindow &windowName);
  void reviseButton(string editname);
  bool clickButton(sf::Event &event);
  string getName();

private:
  string user;
  int pos_x;
  int pos_y;
  float width;
  float height;
  sf::Text label;
  sf::Font font;
};

Button::Button(string name, int posx, int posy){
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
  label.setFont(font);
  label.setCharacterSize(50);
  label.setFillColor(sf::Color::White);
  label.setOutlineColor(sf::Color::Blue);
  label.setOutlineThickness(3);
  label.setString(name);
  label.setPosition(posx, posy);
  width = label.getLocalBounds().width;
  height = label.getLocalBounds().height;
  pos_x = posx;
  pos_y = posy;
  user = name;
}

void Button::reviseButton(string editname){
  user = editname;
  string num = label.getString();
  string placement = num + " " + editname;
  label.setString(placement);
  width = label.getLocalBounds().width;
  height = label.getLocalBounds().height;
}

void Button::showButton(sf::RenderWindow &windowName) {
  windowName.draw(label);
}

string Button::getName(){
  return user;
}

bool Button::clickButton(sf::Event &event){
  int mouseX = event.mouseButton.x;
  int mouseY = event.mouseButton.y;
  if (mouseX < pos_x or mouseX > pos_x+width)
    return false;
  if (mouseY < pos_y or mouseY > pos_y+height)
    return false;
  return true;
}

////////////////// User Information Struct //////////////////
struct userInfo{
  string userName;
  int userScore;
};

/////////////////// Predefine Functions ///////////////////
// GUI Functions
void start(sf::RenderWindow &window);
void userMenu(sf::RenderWindow &window);
void newUser(sf::RenderWindow &window);
void chooseUser(sf::RenderWindow &window);
void pickSong(sf::RenderWindow &window, Button User);
void playGame(sf::RenderWindow &window, Button User, Button Song);
void scores(sf::RenderWindow &window);
void instructions(sf::RenderWindow &window);

// Scoreboard Functions
vector<string> readScores();
void addScores(string user, string score);
void calibrateScores();

/////////////////// Scoreboard Functions ///////////////////
vector<string> readScores(){
  std::ifstream thisfile;
  vector<string> words;
  thisfile.open("highscores.txt");
  string theword;
  while (thisfile >> theword)
    words.push_back(theword);
  thisfile.close(); 
  return words;
}

void addScores(string user, string score){
  vector<string> words = readScores();
  words.push_back(user);
  words.push_back(score);

  std::ofstream newfile("highscores.txt");

  if (words.size() > 0){
  for (int i=0; i<words.size(); i=i+2)
    newfile << words.at(i) << " " << words.at(i+1) << "\n";
  newfile.close();
  }

}

void calibrateScores(){
  vector<string> words = readScores();

  vector<userInfo> userList;
  vector<userInfo> reducedList;
  if (words.size()>0){
    for (int i=0; i<words.size()-1; i=i+2){
      userInfo u;
      u.userName = words.at(i);
      u.userScore = stoi(words.at(i+1));
      userList.push_back(u);
      }

    sort(userList.begin(), userList.end(), [](const userInfo& lhs, const userInfo& rhs) {
      return lhs.userScore > rhs.userScore;
     });

    bool addUser = true;
    reducedList.push_back(userList.at(0));
    for (int i=0; i<userList.size(); i++){
      for (int j=0; j<reducedList.size(); j++){        
        if (userList.at(i).userName == reducedList.at(j).userName) {
          addUser = false;
          break;}
      }
      if (addUser) {
        reducedList.push_back(userList.at(i));
      }
      addUser = true;
    }

    while (reducedList.size()>20){
      reducedList.pop_back();
    }
    std::ofstream newfile("highscores.txt");
    for (auto& w : reducedList){
      newfile << w.userName << " " << w.userScore << "\n";
    }
    newfile.close();
  }
}

/////////////////// Gameplay Functions ///////////////////
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
  return lyrics;}

/////////////////// GUI Functions ///////////////////
void instructions(sf::RenderWindow &window){
  Button Back {"Back",550,650};
  sf::Text Inst;
  sf::Font font;
  string para;
  para = "Greetings\n";
  para += "Welcome to jbchero!\n";
  para += "Type as quickly and accurately ";
  para += "as you can.\n";
  para += "No need to press backspace, ";
  para += "just enter the right characters to "; 
  para += "proceed. \n You will get deducted for ";
  para += "incorrectly entered characters. \n If "; 
  para += "you have what it takes to get on the top 20,\n";
  para += "you will become a returning user. Returning users "; 
  para += "have the \n convenience of skipping making a new profile. ";
  para +=  "Enjoy :)";
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  Inst.setFont(font);
  Inst.setPosition(0, 0);
  Inst.setCharacterSize(20);
  Inst.setFillColor(sf::Color::White);
  Inst.setString(para);

  sf::Event event;

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Back.clickButton(event)) {
            window.clear();  
            start(window);
          }
        }
    Back.showButton(window);
    window.draw(Inst);
    window.display();
    } 
  }  
}

void pickSong(sf::RenderWindow &window, Button User){
  string userName = "User: " + User.getName();
  Button chosenUser{userName, 0, 650};
  Button Choose{"Choose Song:", 0, 0};
  Button Roxanne{"Roxanne - The Police", 0, 100};
  Button Elton{"Your Song - Elton John", 0, 175};
  Button Elvis{"Falling in Love - Elvis", 0, 250};
  Button Rex{"Nothing - Rex Orange County", 0, 325};
  Button Michael{"Merry Christmas - Mike Buble", 0, 400};
  Button Back{"Back", 550, 650};

  sf::Event event;

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Roxanne.clickButton(event)) {
            window.clear();
            playGame(window, User, Roxanne);
          }
          if (Elton.clickButton(event)) {
            window.clear();
            playGame(window, User, Elton);
          }
          if (Elvis.clickButton(event)) {
            window.clear();
            playGame(window, User, Elvis);
          }
          if (Rex.clickButton(event)) {
            window.clear();
            playGame(window, User, Rex);
          }  
          if (Michael.clickButton(event)) {
            window.clear();
            playGame(window, User, Michael);
          }
          if (Back.clickButton(event)) {
            window.clear();
            start(window);
          }        
        }
    Choose.showButton(window);
    Roxanne.showButton(window);
    Elton.showButton(window);
    Elvis.showButton(window);
    Rex.showButton(window);
    Michael.showButton(window);
    chosenUser.showButton(window);
    Back.showButton(window);
    window.display();
    } 
  }  
}  

void playGame(sf::RenderWindow &window, Button User, Button Song){
  string name = User.getName();
  string selection = Song.getName();
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

  sf::Text mylyrics;
  sf::Text mytext;
  sf::Text mypreview;
  sf::Font font;
  sf::Time song_duration;
  sf::Music music;

  sf::Image box;
  box.create(10,10,sf::Color::Yellow);
  box.loadFromFile("jbchero.PNG");

  sf::Texture texture;
  texture.loadFromImage(box);

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(.5,.5);
  sprite.setPosition(175,300);

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
  char mychar;                            // character typed by user
  vector<string> lyrics = buble_lyrics;
  int accuracy;
  int ending;
  string line;
  string current_line;
  int i = 0;                               // iterate through lines in lyrics
  int j = 0;                               // iterate through characters in lines
  int mistakes = 0;  
  int missing = 0;                      // counts mistakenly typed chars
  float char_width;
  vector<int> intervals;


  vector<char> michar;
  vector<char> current_char;
  float char_correct = 0;          // correctly entered chars
  float char_total = 0;              // total entered chars
  float char_nothing = 0;             // count if user doesn't enter anything


  // song selection

  if (selection == "Roxanne - The Police") {
    lyrics = roxanne_lyrics;
    intervals = roxanne_intervals;
    music.openFromFile("roxanne.ogg");
    music.play();
  }

  else if (selection == "Your Song - Elton John") {
    lyrics = your_song_lyrics;
    intervals = your_song_intervals;
    music.openFromFile("your_song.ogg");
    music.play();
  }

  else if (selection == "Falling in Love - Elvis") {
    lyrics = cant_help_lyrics;
    intervals = cant_help_intervals;
    music.openFromFile("cant_help.ogg");
    music.play();
  }

  else if (selection == "Nothing - Rex Orange County") {
    lyrics = nothing_lyrics;
    intervals = nothing_intervals;
    music.openFromFile("nothing.ogg");
    music.play();
  }

  else if (selection == "Merry Christmas - Mike Buble") {
    lyrics = buble_lyrics;
    intervals = buble_intervals;
    music.openFromFile("buble.ogg");
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
                char_total += 1;
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
      window.draw(sprite);
      window.display();
    }
    if (curr_sec == (ending - 1)) {
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

      // std::cout << "accuracy:" << accuracy << "\n";
      string myscore = to_string(floor(accuracy));
      addScores(name, myscore);
      calibrateScores();
      window.clear();
      start(window);
    }
  }
}

void scores(sf::RenderWindow &window){
  calibrateScores();
  Button Back{"Back", 550, 650};
  Button Enter{"High Scores:", 0, 0};

  Button p1{"1:",0,100};
  Button p2{"2:",0,150};
  Button p3{"3:",0,200};
  Button p4{"4:",0,250};
  Button p5{"5:",0,300};
  Button p6{"6:",0,350};
  Button p7{"7:",0,400};
  Button p8{"8:",0,450};
  Button p9{"9:",0,500};
  Button p10{"10:",0,550};

  Button p11{"11:",350,100};
  Button p12{"12:",350,150};
  Button p13{"13:",350,200};
  Button p14{"14:",350,250};
  Button p15{"15:",350,300};
  Button p16{"16:",350,350};
  Button p17{"17:",350,400};
  Button p18{"18:",350,450};
  Button p19{"19:",350,500};
  Button p20{"20:",350,550};

  vector<Button> PlayerList {p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,
                            p11,p12,p13,p14,p15,p16,p17,p18,p19,p20};

  vector<string> words = readScores();

  if (words.size()>0){
  for (int i=0; i<words.size()-1; i=i+2){
    string player = words.at(i);
    string score = words.at(i+1);
    string player_score = player+"  "+score;
    Button& PlayerButton = PlayerList.at(i/2);
    PlayerButton.reviseButton(player_score);
    }
  }

  sf::Event event;
  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Back.clickButton(event)) {
            window.clear();
            start(window);
          }
        }
    Back.showButton(window);
    Enter.showButton(window);
    for (auto& p : PlayerList){
      p.showButton(window);
    }
    window.display();
    } 
  }    
}

void chooseUser(sf::RenderWindow &window){
  calibrateScores();
  Button Back{"Back", 550, 650};
  Button Enter{"Choose:", 0, 0};

  Button p1{"1:",0,100};
  Button p2{"2:",0,150};
  Button p3{"3:",0,200};
  Button p4{"4:",0,250};
  Button p5{"5:",0,300};
  Button p6{"6:",0,350};
  Button p7{"7:",0,400};
  Button p8{"8:",0,450};
  Button p9{"9:",0,500};
  Button p10{"10:",0,550};

  Button p11{"11:",350,100};
  Button p12{"12:",350,150};
  Button p13{"13:",350,200};
  Button p14{"14:",350,250};
  Button p15{"15:",350,300};
  Button p16{"16:",350,350};
  Button p17{"17:",350,400};
  Button p18{"18:",350,450};
  Button p19{"19:",350,500};
  Button p20{"20:",350,550};

  vector<Button> PlayerList {p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,
                            p11,p12,p13,p14,p15,p16,p17,p18,p19,p20};
 
  std::ifstream thisfile;

  vector<string> words = readScores();

  if (words.size()>0){
    for (int i=0; i<words.size()-1; i=i+2){
      string player = words.at(i);
      Button& PlayerButton = PlayerList.at(i/2);
      PlayerButton.reviseButton(player);
    }
  }

  sf::Event event;
  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Back.clickButton(event)) {
            window.clear();
            userMenu(window);}
          for (auto& p : PlayerList){
            if (p.clickButton(event) and words.size()>0){
              window.clear();
              pickSong(window, p);
              break;
            }
          }
        }
    Back.showButton(window);
    Enter.showButton(window);
    for (auto& p : PlayerList){
      p.showButton(window);
    }
    window.display();
    } 
  }    
}

void newUser(sf::RenderWindow &window){
  Button Start{"Start", 200, 350};
  Button Back{"Back", 350, 350};
  Button Enter{"Enter Name:", 200, 200};

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(300, 75));
  rectangle.setOutlineColor(sf::Color::Red);
  rectangle.setOutlineThickness(5);
  rectangle.setPosition(200, 275);

  // Entered Name
  sf::Text enterName;
  sf::Font font;
  string addName;
  char addChar;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  enterName.setFont(font);
  enterName.setPosition(210, 275);
  enterName.setCharacterSize(60);
  enterName.setFillColor(sf::Color::Blue);

  sf::Event event;
  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::TextEntered) {
          if (event.text.unicode < 128){
            addChar = event.text.unicode;
            if (addChar == '\b' and !addName.empty()) {
              addName.pop_back();}
            else if (addName.length() < 7){
            addName.push_back(addChar);}
            enterName.setString(addName);
          }
        }
        if (event.type == sf::Event::MouseButtonPressed){
          if (Start.clickButton(event)) {
            Button NewName{addName,0,0};
            window.clear();
            pickSong(window, NewName);
          }
          if (Back.clickButton(event)) {
            window.clear();
            userMenu(window);
          }
        }
    Start.showButton(window);
    Back.showButton(window);
    Enter.showButton(window);
    window.draw(rectangle);
    window.draw(enterName);
    window.display();
    } 
  }    
}

void userMenu(sf::RenderWindow &window){
  Button New{"New User", 250, 400};
  Button Return{"Returning User", 185, 475};
  Button Back{"Back", 290, 550};

  sf::Image box;
  box.create(10,10,sf::Color::Yellow);
  box.loadFromFile("jbchero.PNG");

  sf::Texture texture;
  texture.loadFromImage(box);

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(.5,.5);
  sprite.setPosition(175,0);

  sf::Event event;

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (New.clickButton(event)) {
            window.clear();
            newUser(window);
          }
          if (Return.clickButton(event)) {
            window.clear();
            chooseUser(window);
          }
          if (Back.clickButton(event)) {
            window.clear();
            start(window);
          }
        }
    New.showButton(window);
    Return.showButton(window);
    Back.showButton(window);
    window.draw(sprite);
    window.display();
    } 
  }    
}


void start(sf::RenderWindow &window){
  Button Play{"Play", 310, 400};
  Button Inst{"Instructions", 225, 475};
  Button Scores{"High Scores", 225, 550};

  sf::Event event;

  sf::Image box;
  box.create(10,10,sf::Color::Yellow);
  box.loadFromFile("jbchero.PNG");

  sf::Texture texture;
  texture.loadFromImage(box);

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(.5,.5);
  sprite.setPosition(175,0);

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Play.clickButton(event)) {
            window.clear();  
            userMenu(window);
          }
          if (Inst.clickButton(event)) {
            window.clear();
            instructions(window);
          }
          if (Scores.clickButton(event)) {
            window.clear();
            scores(window);
          }
        }
    Play.showButton(window);
    Inst.showButton(window);
    Scores.showButton(window);
    window.draw(sprite);
    window.display();
    } 
  }  
}

/////////////////// Main Functions ///////////////////
int main() {
  sf::RenderWindow window(sf::VideoMode(720, 720), "jbcHero Game");
  start(window);
  return 0;
}