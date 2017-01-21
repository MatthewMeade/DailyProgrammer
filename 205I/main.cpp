/*Matthew Meade
 * RPN
 *
 * Input: A string that represents a math expression to be solved
 * Output: The expression in RPM form and the result of the expression
 *
 * r/DailyProgrammer Challenge #205[Intermediate]
 * https://www.reddit.com/2yquvm/
 */


#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


// Function Declarations
bool splitTokens(string line, vector<string> &tokens);
string getNum(string line, int &pos);
bool isDigit(char c);
bool isBracket(char c);
bool isOperator(char c);
bool convert(vector <string> &tokens, string &output);
int precedence(char c);
bool solve(vector<string> tokens, double &result);
unsigned long int fact(int n);

/* Main
 * Read input, parse input, and output result */
int main() {
    vector <string> tokens; // Token = constant, operator, or bracket
    string line; // Line of input

    getline(cin, line);

    // Split line into tokens
    if(!splitTokens(line, tokens)){
        return -1;
    }

    string out;

    // Parse tokens into RPN
    if(!convert(tokens, out)){
        return -1;
    }

    // Convert RPN to tokens
    tokens.clear();
    if(!splitTokens(out, tokens)){
        return -1;
    }

    // Calculate result of expression
    double result;
    if(!solve(tokens, result)){
        return -1;
    }

    // Output result
    cout << out << endl;
    cout << "Result: " << result << endl;

    return 0;
}

/* Split Tokens
 * Splits input string into vector of tokens */
bool splitTokens(string line, vector<string> &tokens){
    for(int i = 0; i < line.length(); i++){ // Loop through each character in the input line

        // If the character is a digit, fetch all following digits
        if(isDigit(line[i])){
            tokens.push_back(getNum(line, i));
        }


        if(line[i] == '/' && line[i+1] == '/'){ // Test if character is a double / for integer division
            tokens.push_back("\\");
            i++;
        }else if(isOperator(line[i]) || isBracket(line[i])){ // Test if character is a bracket or operator
            tokens.push_back(string(1,line[i]));
        }

        // If the character doesn't fit any valid value, end the program
        else if(line[i] != ' ' && line[i] != 0){
            cout << "Invalid Character: " << line[i] << endl;
            return false;
        }
    }
    return true;
}

/* getNum
 * Get string of digits until non digit is detected
 * Modifies index so that the splitTokens iterator can skip digits already collected*/
string getNum(string line, int &pos){
    string s = "";
    while(isDigit(line[pos])){
        s += line[pos++];
    }
    return s;
}

/* isDigit
 * Tests if a character is a digit */
bool isDigit(char c){
    return c >= '0' && c <= '9';
}

/* isBracket
 * Tests if a character is a bracket */
bool isBracket(char c){
    return c == '(' ||
           c == ')';
}

/* isOperator
 * Tests is a character is a valid operator */
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

/* precedence
 * Returns order of operations precedence value of an operator */
int precedence(char c){
    if(c == '+' || c == '-') return 0;
    if(c == '/' || c == '%' || c == '\\' || c == 'x' || c== '*') return 1;
    if(c == '^') return 2;
    if(c == '!') return 3;
    return -1;
}

/* convert
 * Converts a standard expression to its RPN equivalent
 * Uses the shunting-yard algorithm */
bool convert(vector <string> &tokens, string &output){
    string token;
    vector <string> stack;

    //Loop through all the tokens
    for(int i = 0; i < tokens.size(); i++){
        token = tokens[i];

        // If the token is a number, push it to the output queue
        if(isDigit(token[0])){
            output += token;
            output += ' ';
            continue;
        }

        // If the token is an operator
        if(isOperator(token[0])){
            // While an operator is on the stack and the current token has a lower than or equal precedence to that operator
            while(stack.size() > 0 && precedence(token[0]) <= precedence(stack[0][0])){
                // Pop the operator off the stack into the output queue
                output += stack[0];
                output += ' ';
                stack.erase(stack.begin());
            }
            // Push token to stack
            stack.insert(stack.begin(),token);
            continue;
        }

        // If the token is a left parenthesis push it to the stack
        if(token[0] == '('){
            stack.insert(stack.begin(),token);
            continue;
        }

        // If the token is a right parenthesis
        if(token[0] == ')'){
            // Loop until the matching left parenthesis is found
            while(stack.size() > 0 && stack[0] != "("){
                // Push top operator to output queue
                output += stack[0];
                output += ' ';
                stack.erase(stack.begin());
            }

            // If the stack is empty, the matching parenthesis was not found
            if(stack.size() == 0){
                cout << "Mismatched Parentheses" << endl;
                return false;
            }

            // Pop the left parenthesis
            stack.erase(stack.begin());
        }

    }

    // While there are still operators on the stack
    while(stack.size() > 0){
        // If there is a parenthesis on the stack, it is mismatched
        if(isBracket(stack[0][0])){
            cout << "Mismatched Parentheses" << endl;
            return false;
        }

        //Pop the operator onto the output queue
        output += stack[0];
        output += ' ';
        stack.erase(stack.begin());
    }

    return true;
}


/* solve
 * Solves a RPN expression stored in tokens and stores the result*/
bool solve(vector<string> tokens, double &result){
    vector <string> stack;
    string token;

    // Loop through all tokens
    for(int i = 0; i < tokens.size(); i++){

        token = tokens[i];

        // If the token is a value, push it onto the stack
        if(!isOperator(token[0])){
            stack.insert(stack.begin(),token);
        }else{ // Else, the token is an operator

            // Calculate how many arguments are required
            int numArgs = (token[0] == '!') ? 1 : 2;

            // Check to ensure there are enough arguments
            if(stack.size() < numArgs){
                cout << "Invalid values" << endl;
                return false;
            }

            // Arguments for operator
            double n1 = 0;
            double n2 = 0;

            // Pop arguments from the stack
            if(numArgs == 2){
                n1 = stod(stack[1]);
                n2 = stod(stack[0]);
                stack.erase(stack.begin(), stack.begin()+2);
            }else{
                n1 = stod(stack[0]);
                stack.erase(stack.begin());
            }


            double r = 0; // Result of operation

            // Preform operation=
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

            // Push result to stack
            stack.insert(stack.begin(),to_string(r));
        }
    }

    // If there is only one value in the stack, it is the result
    if(stack.size() == 1) {
        result = stod(stack[0]);
        return true;
    }
    else { // Otherwise, the input is invalid
        cout << "Invalid input" << endl;
        return false;
    }

}

/* fact
 * Returns factorial of input n */
unsigned long int fact(int n){
    return (n > 1) ? n * fact(n-1) : 1;
}

