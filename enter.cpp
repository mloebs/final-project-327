// Team 12: Type 2 Learn
// Summary:

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
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
// Scoreboard Functions
vector<string> readScores();
void addScores();
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

  for (int i=0; i<words.size(); i=i+2)
    newfile << words.at(i) << " " << words.at(i+1) << "\n";
  newfile.close();

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

/////////////////// GUI Functions ///////////////////
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
            std::cout << "Roxanne";
            window.clear();
            playGame(window, User, Roxanne);
          }
          if (Elton.clickButton(event)) {
            std::cout << "Elton";
            window.clear();
          }
          if (Elvis.clickButton(event)) {
            std::cout << "Elvis";
            window.clear();
          }
          if (Rex.clickButton(event)) {
            std::cout << "Rex";
            window.clear();
          }  
          if (Michael.clickButton(event)) {
            std::cout << "Michael";
            window.clear();
          }
          if (Back.clickButton(event)) {
            std::cout << "Back";
            window.clear();
            chooseUser(window);
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
  std::cout << name;
  Button Play{name, 310, 0};
  sf::Event event;

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Play.clickButton(event)) {
            std::cout << "Play";
            window.clear();
            addScores(name, "100");
            calibrateScores();
            userMenu(window);
          }
        }
    Play.showButton(window);
    window.display();
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
            std::cout << "Back";
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
            std::cout << "Back";
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

  sf::Event event;
  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Start.clickButton(event)) {
            std::cout << "Start";
            window.clear();
          }
          if (Back.clickButton(event)) {
            std::cout << "Back";
            window.clear();
            userMenu(window);
          }
        }
    Start.showButton(window);
    Back.showButton(window);
    Enter.showButton(window);
    window.draw(rectangle);
    window.display();
    } 
  }    
}

void userMenu(sf::RenderWindow &window){
  Button New{"New User", 250, 400};
  Button Return{"Returning User", 185, 475};
  Button Back{"Back", 290, 550};

  sf::Event event;

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (New.clickButton(event)) {
            std::cout << "New";
            window.clear();
            newUser(window);
          }
          if (Return.clickButton(event)) {
            std::cout << "Return";
            window.clear();
            chooseUser(window);
          }
          if (Back.clickButton(event)) {
            std::cout << "Return";
            window.clear();
            start(window);
          }
        }
    New.showButton(window);
    Return.showButton(window);
    Back.showButton(window);
    window.display();
    } 
  }    
}


void start(sf::RenderWindow &window){
  Button Play{"Play", 310, 400};
  Button Inst{"Instructions", 225, 475};
  Button Scores{"High Scores", 225, 550};

  sf::Event event;

  while (window.isOpen()){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::MouseButtonPressed){
          if (Play.clickButton(event)) {
            std::cout << "Play";
            window.clear();  
            userMenu(window);
          }
          if (Inst.clickButton(event)) {
            std::cout << "Instructions";
            window.close();
          }
          if (Scores.clickButton(event)) {
            std::cout << "High Scores";
            window.clear();
            scores(window);
          }
        }
    Play.showButton(window);
    Inst.showButton(window);
    Scores.showButton(window);
    window.display();
    } 
  }  
}

/////////////////// Main Functions ///////////////////
int main() {
  sf::RenderWindow window(sf::VideoMode(720, 720), "Type2Learn Game");
  start(window);
  return 0;
}