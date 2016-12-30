/*Matthew Meade
 * Simplifying fractions (Variables)
 *
 * Given a list of equations and a list of fractions containing only letters
 * Outputs simplified fractions
 *
 * r/DailyProgrammer Challenge #277[Easy]
 * https://www.reddit.com/r/dailyprogrammer/comments/4uhqdb/20160725_challenge_277_easy_simplifying_fractions/
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Function Declarations
void splitLine(string line, string &a, string &b);
void simplify(string &a, string &b);
bool isBonus(string line);
int gcd(int a, int b);
void convertLine(string line, int &a, int &b);

//Global parallel vectors storing equations
std::vector<char> vars;
std::vector<string> eqs;

/* Main
 * Reads equations and fractions from user
 * Output simplified fractions */
int main(int argc, char* argv[]) {

    string line = "";

    //Read a line from cin that specifies how many equations there are
    string numEqS = "";
    getline(cin, numEqS);
    int numEq = stoi(numEqS);

    //Loop through the specified amount of lines to read in thr equations
    for(int i = 0; i < numEq; i++){
        getline(cin, line);

        //Split line into two separate strings
        string a, b;
        splitLine(line, a, b);

        //Add variable and equation to vectors
        vars.push_back(a[0]);
        eqs.push_back(b);
    }


    getline(cin, line);
    //Loop until user enters blank line
    while(line.length()){

        if(!isBonus(line)){
            //a = numerator, b = denominator, g = greatest common divisor
            int a, b, g;

            //Split line into two ints
            convertLine(line, a, b);

            //Calculate greatest common divisor of both ints
            g = gcd(a, b);

            //Divide numerator and denominator by gcd to simply fraction
            cout << a / g << " " << b / g << endl;
        }else{
            //Split line into numerator and denominator
            string a, b;
            splitLine(line, a, b);

            //Simplify fraction
            simplify(a, b);

            //Output simplified fraction
            cout << a << " " << b << endl;
        }


        getline(cin, line);
    }

    return 0;
}

/* SplitLine
 * Splits line at space and assigns each part to strings a and b */
void splitLine(string line, string &a, string &b){

    //Locate position of space
    size_t spos = line.find(" ");

    //Loop through chars until space and append each char to a
    for(int i = 0; i < spos; i++){
        a.insert(a.length(), 1, line[i]);
    }

    //Loop thorough rest of string and append each char to b
    for(int i = spos + 1; line[i]; i++){
        b.insert(b.length(), 1, line[i]);
    }
}

/* Simplify
 * Takes numerator and denominator and simplifies them
 * First expands equations then removes chars that appear in both numerator and denominator */
void simplify(string &a, string &b){


    bool changes = true;
    //Loop until numerator and denominator are fully expanded
    while(changes) {
        changes = false;

        //Loop through all expandable variables
        for(int i = 0; i < vars.size(); i++){

            //Test if expandable variable is found in numerator
            size_t pos = a.find_first_of(vars[i], 0);
            if(pos != string::npos){
                //Append expanded form of variable and erase old one
                a.append(eqs[i]);
                a.erase(pos, 1);
                changes = true;
            }

            //Test if expandable variable is found in numerator
            pos = b.find_first_of(vars[i], 0);
            if(pos != string::npos){
                //Append expanded form of variable and erase old one
                b.append(eqs[i]);
                b.erase(pos, 1);
                changes = true;
            }
        }

    }

    //Loop through all variables in numerator
    for(int i = 0; a[i]; i++){

        //Test if variable is also in denominator
        size_t pos = b.find_first_of(a[i], 0);
        if(pos != string::npos){
            //Erase variable from numerator and denominator
            a.erase(i, 1);
            b.erase(pos, 1);
            i--; //Shift i back to prevent skipping chars
        }
    }

    //If all variables have been cancelled out append 1
    if(a.length() == 0) a.append("1");
    if(b.length() == 0) b.append("1");

}

/* GCD
 * Takes two integers
 * Recursively calculates greatest common divisor of integers using Euclidean algorithm */
int gcd(int a, int b) {
    return b ? gcd(b, a % b): a;
}

/* ConvertLine
 * Takes a string and a pointer to two integers
 * Assigns two ints found in string a and  */
void convertLine(string line, int &a, int &b){
    //Locate space separating numbers
    size_t spos = line.find(" ");
    line[spos] = 0; //Replace space with null

    //Convert each part of the string to an int
    a = stoi(line);
    b = stoi(&line[spos + 1]);
}

bool isBonus(string line){
    for(int i = 0; line[i]; i++){
        if(line[i] == ' ') continue;
        if(line[i] < '0' || line[i] > '9'){
            return true;
        }
    }
    return false;
}

