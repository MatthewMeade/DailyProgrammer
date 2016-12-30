/*Matthew Meade
 * Text Reflow
 *
 * Break up lines so they fit within a certain width
 *
 * Input: Text with a maximum line width of 80 characters
 * Output: Same text as input but with a maximum line width of 40 characters
 *
 * Bonus: Output the text with full justification
 *
 * r/DailyProgrammer Challenge #279[Intermediate]
 * https://www.reddit.com/4ybbcz/
 */

#include <iostream>
#include <string>
#include <vector>

// Number of columns to output text
#define COLS 40

using namespace std;

// Function Declarations
void splitInput(string line, vector<string> &words);
void joinWords(vector <string> words, vector <string> &lines);
void justifyLines(vector <string> &lines);


/* Main
 * Read inputs until a blank line is entered, then format and output text */
int main() {

    vector <string> words;
    vector <string> lines;

    string line; // line of input
    getline(cin, line);

    // Loop until user enters blank line
    while(line.length()){
        // Split line up into words and store them in a vector
        splitInput(line, words);
        getline(cin, line);
    }

    // Join individual words into lines then justify the lines
    joinWords(words, lines);
    justifyLines(lines);

    // Output each line
    for(int i = 0; i < lines.size(); i++){
        cout << lines[i] << endl;
    }
    return 0;
}

/* Split Input
 * Split a string at every space storing the results in a vector */
void splitInput(string line, vector<string> &words){
    string w = ""; // Current word
    for(int i = 0; line[i]; i++){ // Loop through every character
        if(line[i] == ' '){
            // Add word to vector and reset it
            words.push_back(w);
            w = "";
        }else{
            // Add the current character to the word
            w += line[i];
        }
    }

    // Add the final word to the vector
    words.push_back(w);
}

/* Join Words
 * Generates a vector of lines from a list of words
 * Each line fits within the column limit */
void joinWords(vector <string> words, vector <string> &lines){
    string l = ""; // Current line of text
    for(int i = 0; i < words.size(); i++){ // Loop through all the words
        // Test if the current words fits within the column limit
        if(l.length() + words[i].length() > COLS){
            l.pop_back(); // Remove extra space
            lines.push_back(l); // Add line to vector
            l = ""; // Reset line
        }

        l += words[i]; // Add current word to line
        l += " "; // Separate next word with a space
    }
    // Remove extra space and add last line to vector
    l.pop_back();
    lines.push_back(l);
}

/* Justify Lines
 * Loops through a vector of strings and expands their spaces
 * so that they are all a consistent length*/
void justifyLines(vector <string> &lines){
    for(int i = 0; i < lines.size(); i++){ // Loop through all the lines
        size_t sf = lines[i].find_first_of(' '); // Location of first space
        size_t sl = lines[i].find_last_of(' '); // Location of last space

        // Loop while the line isn't long enough
        // Start at the last space in the list and work backwards
        while(lines[i].length() < COLS){
            // Insert a space at current location
            lines[i].insert(sl, " ");

            // Move to the previous space if there is one
            // Otherwise move back to the end
            sl = sl > sf ?  lines[i].find_last_of(" ", sl - 1) : lines[i].find_last_of(' ');
        }
    }
}