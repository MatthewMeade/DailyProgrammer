/*Matthew Meade
 * Defusing the bomb
 *
 * Given a list of wires cut detect if bomb exploded based on a set of rules
 * Outputs if bomb was defused or exploded
 *
 * r/DailyProgrammer Challenge #293[Easy]
 * https://www.reddit.com/5e4mde/
 */
#include <iostream>
#include <string>

using namespace std;

bool cmpWires(char w1, char w2);

/* Main 
 * Read input until user enters a blank line
 * Output if bomb was sucessfully defused  */
int main() {

    //w1 was the last wire cut and w2 is the wire currently being cut
    string w1, w2;
    
    //flag true when bomb explodes
    bool exploded = false;

    //Read first and second lines
    getline(cin, w1);
    getline(cin, w2);

    //Loop until a blank line is entered
    while(w2.length() > 0){
        //Compare current wire with last cut wire 
        exploded = exploded || cmpWires(w1[0], w2[0]);

        //Set current wire to last wire and get new wire
        w1 = w2;
        getline(cin, w2);
    }

    //Output if bomb exploded or was defused
    cout << (exploded ? "Boom" : "Bomb Defused") << endl;

    return 0;
}

/* cmpWires
 * Takes in two chars and tests if they are valud based on a set of rules 
 * Retuns true if bomb will explode */
bool cmpWires(char w1, char w2){
    switch (w1){
        case 'w': return (w2 == 'w' || w2 == 'b'); // After cutting w, w or b must not be cut
        case 'r': return (w2 != 'g'); // After cutting r, g must be cut
        case 'b': return (w2 == 'w' || w2 == 'g' || w2 == 'o'); // After cutting b, w, g, or o must not be cut
        case 'o': return (w2 != 'r' && w2 != 'b'); // After cutting o, r or b must be cut
        case 'g': return (w2 != 'o' && w2 != 'w'); // After cutting g, o or w must be cut
        case 'p': return (w2 != 'b' && w2 != 'r'); // After cutting p, b or r must be cut
        default: return false;
    }
}