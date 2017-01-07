#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool splitTokens(string line, vector<string> &tokens);
string getNum(string line, int &pos);
bool isDigit(char c);
bool isBracket(char c);
bool isOperator(char c);
bool convert(vector <string> &tokens, string &output);
int precedence(char c);
bool solve(vector<string> tokens, double &result);
int fact(int n);


int main() {
    vector <string> tokens;
    string line;

    getline(cin, line);

    if(!splitTokens(line, tokens)){
        return -1;
    }

//    for(int i = 0; i < tokens.size(); i++) cout << tokens[i] << " ~ " << endl;

    string out;

    if(!convert(tokens, out)){
        return -1;
    }

    tokens.clear();
    if(!splitTokens(out, tokens)){
        return -1;
    }


    double result;
    if(!solve(tokens, result)){
        return -1;
    }

    cout << out << endl;
    cout << "Result: " << result << endl;

    return 0;
}

bool splitTokens(string line, vector<string> &tokens){
    for(int i = 0; line[i]; i++){

        if(isDigit(line[i])){
            tokens.push_back(getNum(line, i));
        }

        if(line[i] == '/' && line[i+1] == '/'){
            tokens.push_back("\\");
            i++;
        }else if(isOperator(line[i]) || isBracket(line[i])){
            tokens.push_back(string(1,line[i]));
        }

        if(!isOperator(line[i]) && !isDigit(line[i]) && !isBracket(line[i]) && line[i] != ' ' && line[i] != 0){
            cout << "Invalid Character: " << (int)line[i] << endl;
            return false;
        }
    }
    return true;
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
           c == '*' ||
           c == '^' ||
           c == '!' ||
           c == '%' ||
           c == '\\';
}

int precedence(char c){
    if(c == '+' || c == '-') return 0;
    if(c == '/' || c == '%' || c == '\\' || c == 'x' || c== '*') return 1;
    if(c == '^') return 2;
    return -1;
}

bool convert(vector <string> &tokens, string &output){
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

            if(stack.size() == 0){
                cout << "Mismatched Parentheses" << endl;
                return false;
            }
            stack.erase(stack.begin());
        }

    }

    while(stack.size() > 0){
        if(isBracket(stack[0][0])){
            cout << "Mismatched Parentheses" << endl;
            return false;
        }
        output += stack[0];
        output += ' ';
        stack.erase(stack.begin());
    }

    return true;
}

bool solve(vector<string> tokens, double &result){
    vector <string> stack;
    string token;

    for(int i = 0; i < tokens.size(); i++){

        token = tokens[i];

        if(!isOperator(token[0])){
            stack.insert(stack.begin(),token);
        }else{

            int numArgs = (token[0] == '!') ? 1 : 2;

            if(stack.size() < numArgs){
                cout << "Invalid values" << endl;
                return false;
            }

            double n1 = 0;
            double n2 = 0;

            if(numArgs == 2){
                n1 = stod(stack[1]);
                n2 = stod(stack[0]);
                stack.erase(stack.begin(), stack.begin()+2);
            }else{
                n1 = stod(stack[0]);
                stack.erase(stack.begin());
            }


            double r = 0;

            switch (token[0]){
                case '+': r = n1 + n2; break;
                case '-': r = n1 - n2; break;
                case '/': r = n1 / n2; break;
                case 'x': case '*': r = n1 * n2; break;
                case '^': r = pow(n1, n2); break;
                case '%': r = (int)n1 % (int)n2; break;
                case '\\': r = (int) n1 / (int) n2; break;
                case '!': r = fact((int) n1); break;
                default: cout << "Invalid Operator" << endl;
            }
            stack.insert(stack.begin(),to_string(r));
        }
    }

    if(stack.size() == 1) {
        result = stod(stack[0]);
        return true;
    }
    else {
        cout << "Invalid input" << endl;
        return false;
    }

}

int fact(int n){
    return (n > 1) ? n * fact(n-1) : 1;
}

