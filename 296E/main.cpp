/*Matthew Meade
 * The Twelve Days of
 *
 * Print out the lyrics of The Twelve Days of Christmas
 * Bonus 1: Use words in the song instead of numbers
 * Bonus 2: Recieve the gifts from input
 *
 * r/DailyProgrammer Challenge #296[Easy]
 * https://www.reddit.com/5j6ggm/
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function Declarations
void song(int n);
void LoadGifts(const char* name);

// Global arrays storing days and gifts
const string days[] = {"first", "second", "third", "fourth", "fifth", "sixth",
                       "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth"};

const string nums[] = {"and a", "two", "three", "four", "five", "six",
                       "seven", "eight", "nine", "ten", "eleven", "twelve"};

string gifts[12] = {"Partridge in a Pear Tree", "Turtle Doves", "French Hens",
                    "Calling Birds", "Golden Rings", "Geese a Laying",
                    "Swans a Swimming", "Maids a Milking", "Ladies Dancing",
                    "Lords a Leaping", "Pipers Piping", "Drummers Drumming"};

// Number of loops to make (If user doesn't specify 12 gifts)
int maxDays = 11;


int main(int argc, char* argv[]) {

    // Ensure proper argument usage
    if(argc > 2) {
        cout << "Usage: " << argv[0] << " [file]" << endl;
        return -1;
    }

    // If user specified a file name, load in that file
    if(argc == 2) {
        LoadGifts(argv[1]);
    }

    // Start printing the song
    song(0);
    return 0;
}

/* Song 
 * Prints the lyrics for the nth day of cristmas 
 * Recursively loop through verses by calling song(n+1) until n < maxDays */
void song(int n){

    cout << "On the " << days[n] << " day of Christmas" << endl;
    cout << "my true love sent  to me:" << endl;

    // Loop from gift n to 0 and output gift
    for (int i = n; i >= 0; i--){
        cout << nums[i] << " " << gifts[i] << endl;
    }

    // Blank line between verses
    cout << endl;

    // Print again starting at next verse
    if(n < maxDays) song(n + 1);
    
}

/* LoadGifts 
 * Read file into gifts array
 * If less that 12 gifts are listed, limit printed verses to those gifts */
void LoadGifts(const char* name){

    // Open file
    fstream file;
    file.open(name, ios::in);

    // Warn user if file could not be opened
    if(file == NULL){
        cout << "Could not open file " << name << ". Using default gifts\n" << endl;
        file.close();
        return;
    }

    // Loop though file until end or 12 gifts have been loaded
    maxDays = 0;
    for (int i = 0; i < 12; ++i) {
        getline(file, gifts[i]);
        if(file.eof()){
            break;
        }
        // Increment number of days to print
        maxDays ++;
    }

    // Close file
    file.close();
}