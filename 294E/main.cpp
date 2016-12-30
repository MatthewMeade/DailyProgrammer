/*Matthew Meade
 * Rack management 1
 *
 * Given 7 letter tiles and a word, determine if word can be created with those tiles
 * Bonus 1: Handle blank tiles represented by a '?'
 * Bonus 2: Given 20 tiles, determine the longest word that can be formed using a word list
 * Bonus 3: Given 20 tiles, determine the highest scoring word that can be formed using a word list
 *
 * r/DailyProgrammer Challenge #294[Easy]
 * https://www.reddit.com/5go843/
 */
 
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//Function Declarations
bool scrabble(string letters, string word);
string longest(string letters);
string highest(string letters);
int score(string letters, string word);

/* Main
 * Call functions with hard coded test values and print the results */
int main(int argc, char* argv[]) {

    // Main Challenge
    cout << "Main Challenge:" << endl;
    cout << (scrabble("ladilmy", "daily") ? "True" : "False") << endl;
    cout << (scrabble("eerriin", "eerie") ? "True" : "False") << endl;
    cout << (scrabble("orrpgma", "program") ? "True" : "False") << endl;
    cout << (scrabble("orppgma", "program") ? "True" : "False") << endl;

    // Bonus 1
    cout << endl << "Bonus 1:" << endl;
    cout << (scrabble("pizza??", "pizzazz") ? "True" : "False") << endl;
    cout << (scrabble("piizza?", "pizzazz") ? "True" : "False") << endl;
    cout << (scrabble("a??????", "program") ? "True" : "False") << endl;
    cout << (scrabble("b??????", "program") ? "True" : "False") << endl;

    // Bonus 2
    cout << endl << "Bonus 2:" << endl;
    cout << longest("dcthoyueorza") << endl;
    cout << longest("uruqrnytrois") << endl;
    cout << longest("rryqeiaegicgeo??") << endl;
    cout << longest("udosjanyuiuebr??") << endl;
    cout << longest("vaakojeaietg????????") << endl;

    // Bonus 3
    cout << endl << "Bonus 3:" << endl;
    cout << highest("dcthoyueorza") << endl;
    cout << highest("uruqrnytrois") << endl;
    cout << highest("rryqeiaegicgeo??") << endl;
    cout << highest("udosjanyuiuebr??") << endl;
    cout << highest("vaakojeaietg????????") << endl;

    return 0;
}

/* Scrabble
 * Take in a sting of tiles and a word
 * Determine if word can be created using tiles */
bool scrabble(string letters, string word){
  
    // Loop through each letter of the word
    for(int i = 0; word[i]; i++){

        //Check if current letter or a blank is in the list of tiles
        size_t letterPos = letters.find_first_of(word[i]);
        size_t wildPos = letters.find_first_of('?');

        // If letter is found, remove it
        if(letterPos != string::npos){
            letters[letterPos] = '_';
        } else if(wildPos != string::npos){
            letters[wildPos] = '_';
        }else{
            // Return false if letter is not found in tiles
            return false;
        }
    }
    return true;
}

/* Longest 
 * Take in a list of tiles
 * Loop through word list and find longest word that can be created using tiles */
string longest(string letters){

    // Open file
    ifstream file("enable1.txt");
    string line; // Current word
    string longestStr = ""; // Longest found word

    // Warn user if file cannot be opened
    if(!file) return "Cannot open file enable1.txt";

    // Loop through word list file
    while(!file.eof()){
        getline(file, line);
        
        // Replace end character with null terminator
        line[line.length() - 1] = 0;

        //Check if current word is longer than current longest and if it can be made using the tiles
        if(line.length() > longestStr.length() && scrabble(letters, line)){
            longestStr = line;
        }
    }
    
    // Close file and return longest word
    file.close();
    return longestStr;

}

/* Highest 
 * Take in a list of tiles and find the higest scoring word that can be created using tiles */
string highest(string letters){
  
    // Open file
    ifstream file("enable1.txt");
    string line; // Current word
    int highestScore = 0; // Score of higest scoring word
    string highestStr = ""; //Highest scoring word

    // Warn user if file cannot be opened
    if(!file) return "Cannot open file enable1.txt";

    // Loop through word list file
    while(!file.eof()){
        getline(file, line);
        
        // Replace last char of line with null terminator
        line[line.length() - 1] = 0;

        // Calculate score of cuttent line
        int lineScore = score(letters, line);
        
        // Check if current score is higher than highest score and if word can be created from tiles
        if(lineScore > highestScore && scrabble(letters, line)){
            highestScore = lineScore;
            highestStr = line;
        }

    }

    // Close file and return highest score
    file.close();
    return highestStr;
}

int scores[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

/* Score 
 * Take in word and tiles used to create that word
 * Calculate score of word based on scores[] array */
int score(string letters, string word){

    // Score
    int c = 0;

    // Loop through all the tiles
    for(int i = 0; letters[i]; i++){
      
        //Check if tile was used in word
        size_t letterPos = word.find_first_of(letters[i]);
        if(letterPos != string::npos){
            // Add value of tile to score
            c += scores[word[letterPos] - 97];
            // Remove letter from word so it doesn't get scored again
            word[letterPos] = '_';
        }
    }
    
    // Return score
    return c;

}
