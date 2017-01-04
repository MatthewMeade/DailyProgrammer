#include <iostream>
#include <string>
#include <vector>

using namespace std;

void splitTokens(string line, vector<string> &tokens);
string getNum(string line, int &pos);
bool isDigit(char c);
bool isBracket(char c);
bool isOperator(char c);
void convert(vector <string> &tokens, string &output);
int precedence(char c);
double solve(vector<string> tokens);


int main() {
    vector <string> tokens;
    string line;

    getline(cin, line);

    splitTokens(line, tokens);

//    for(int i = 0; i < tokens.size(); i++) cout << tokens[i] << endl;
    cout << endl;

    string out;
    convert(tokens, out);
    cout << out << endl;

    tokens.clear();
    splitTokens(out, tokens);

//    for(int i = 0; i < tokens.size(); i++) cout << tokens[i] << endl;

    double result = solve(tokens);
    cout << "Result: " << result << endl;

    return 0;
}

void splitTokens(string line, vector<string> &tokens){
    for(int i = 0; line[i]; i++){
        if(isDigit(line[i])){
            tokens.push_back(getNum(line, i));
        }
        if(isOperator(line[i]) || isBracket(line[i])){
            tokens.push_back(string(1,line[i]));
        }
    }
}

string getNum(string line, int &pos){
    string s = "";
    while(isDigit(line[pos])){
        s += line[pos++];
    }
    return s;
}

bool isDigit(char c){
    return c >= '0' && c <= '9';
}

bool isBracket(char c){
    return c == '(' ||
           c == ')';
}

bool isOperator(char c){
    return c == '+' ||
           c == '-' ||
           c == '/' ||
           c == 'x' ||
           c == '*';
}

int precedence(char c){
    if(c == '+' || c == '-') return 0;
    if( c== '/' || c == 'x' || c== '*') return 1;
    return -1;
}

void convert(vector <string> &tokens, string &output){
    string token;
    vector <string> stack;
    for(int i = 0; i < tokens.size(); i++){
        token = tokens[i];
        if(isDigit(token[0])){
            output += token;
            output += ' ';
            continue;
        }

        if(isOperator(token[0])){
            while(stack.size() > 0 && precedence(token[0]) <= precedence(stack[0][0])){
                output += stack[0];
                output += ' ';
                stack.erase(stack.begin());
            }
            stack.insert(stack.begin(),token);
            continue;
        }

        if(token[0] == '('){
            stack.insert(stack.begin(),token);
            continue;
        }

        if(token[0] == ')'){
            while(stack.size() > 0 && stack[0] != "("){
                output += stack[0];
                output += ' ';
                stack.erase(stack.begin());
            }

            stack.erase(stack.begin());
        }

    }

    while(stack.size() > 0){
        output += stack[0];
        output += ' ';
        stack.erase(stack.begin());
    }
}

double solve(vector<string> tokens){
    vector <string> stack;
    string token;

    for(int i = 0; i < tokens.size(); i++){
        token = tokens[i];
//        cout << "Token: " << token << endl;
        if(!isOperator(token[0])){
            stack.insert(stack.begin(),token);
        }else{
            double n1 = stod(stack[1]);
            double n2 = stod(stack[0]);
            stack.erase(stack.begin(), stack.begin()+2);

            double r = 0;

            switch (token[0]){
                case '+': r = n1 + n2; break;
                case '-': r = n1 - n2; break;
                case '/': r = n1 / n2; break;
                case 'x': case '*': r = n1 * n2; break;
                default: cout << "Invalid Operator" << endl;
            }
            stack.insert(stack.begin(),to_string(r));
        }
    }

    if(stack.size() == 1) return stod(stack[0]);
    else cout << "Invalid input" << endl;
    return 0;

}