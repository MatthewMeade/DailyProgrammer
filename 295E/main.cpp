/*Matthew Meade
 * Letter by letter
 *
 * Change a string into another string, letter by ketter
 *
 * r/DailyProgrammer Challenge #295[Easy]
 * https://www.reddit.com/5hy8sm/
 */

#include <iostream>
#include <string>
using namespace std;

int main() {

    // Read in the two strings
    string word1, word2;
    cin >> word1; cin >> word2;

    //Output initial line
    cout << endl << word1 << endl;
    
    // Loop through each letter in word 2 and replace it with the letter in word 1
    for(int i = 0; word2[i]; i++){
      word1[i] = word2[i];
      // Output result
      cout << word1 << endl;
    }

    return 0;
}