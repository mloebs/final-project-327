// Basic Script Framework for calculating accuracy for given sentence
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::cin;
using std::cout;


int main()

{
    std::string a = "The car went sixty miles per hour on the highway." ,
                b = "the car want sixty mless per hour on the highway";
    int errors = 0;

    for( auto i( a.begin() ); i != a.end(); ++i )
    {
        if( *i != *( b.begin() + std::distance( a.begin() , i ) ) ) ++errors;
    }
    std::cout << "There was a total of " << errors << " errors in the sentence with " << a.size() << " letters." << std::endl;
    std::cout << "Your accuracy is %" << static_cast<double>( ( a.size() - errors ) ) / a.size()  * 100 << '.' << std::endl;
}


// {   string A = "Real gs move in silence like lasagna";

//     string B;
//     std::vector<char> a;
//     std::vector<char> b;

//     cout << "Type lyric:" << "\n";
//     cin >> B;
//     int errors = 0;

//     for (auto letter: B){
//       b.push_back(letter);

//     }

//     for(auto letter_match: A)
//     {
//       a.push_back(letter_match);
        
//     }

//     for (int i =0; i<b.size(); i++){
//       cout << a.at(i) << "\n";
//       //cout << b.at(i) << "\n";
//       if (a.at(i) != b.at(i)) errors++;
//     }
//   }
