#include <iostream>
#include <string>
#include <vector>

using namespace std;

void splitTokens(string line, vector<string> &tokens);
string getNum(string line, int &pos);
bool charIsDigit(char c);
bool isValidChar(char c);


int main() {
    vector <string> tokens;
    string line, output;

    getline(cin, line);

    splitTokens(line, tokens);

    for(int i = 0; i < tokens.size(); i++){
        cout << tokens[i];
    }

    cout << endl;
    return 0;
}

void splitTokens(string line, vector<string> &tokens){
    for(int i = 0; line[i]; i++){
        if(charIsDigit(line[i])){
            tokens.push_back(getNum(line, i));
        }
        if(isValidChar(line[i])){
            tokens.push_back(string(1,line[i]));
        }
    }
}

string getNum(string line, int &pos){
    string s = "";
    while(pos < line.length() && line[pos] >= '0' && line[pos] <= '9'){
        s += line[pos++];
    }
    return s;
}

bool charIsDigit(char c){
    return c >= '0' && c <= '9';
}

bool isValidChar(char c){
    return c == '+' ||
           c == '-' ||
           c == '/' ||
           c == 'x' ||
           c == '*' ||
           c == '(' ||
           c == ')';
}