/*Matthew Meade
 * Intersecting Area Of Overlapping Rectangles
 *
 * Finds the area that two or more rectangles overlap
 *
 * Each line of input contains the x and y positions of
 * the opposite corners of a rectangle
 *
 * Outputs the area that the rectangles overlap
 *
 *
 *
 * r/DailyProgrammer Challenge #296[Intermediate]
 * https://www.reddit.com/5jpt8v/
 */

#include <iostream>
#include <vector>
#include "Rect.h"

using namespace std;


// Function Declaration
void SplitLine(string line, double (&result)[4]);

/* Main
 * Reads input until user enters empty string
 * Builds each rectangle based on the input and combines them into one rectangle
 * Outputs the area of the final rectangle, or 0 if some don't overlap */
int main() {

    // Rectangles
    vector <Rect> rects;

    string line; // Input
    double result[4]; // Coordinates of the rectangle points

    getline(cin, line);
    while(line.length()){ // Loop until user enters blank line
        //Convert the input into an array of doubles
        SplitLine(line, result);

        // Create new rectangle with input coordinates
        Rect r(result[0], result[1], result[2], result[3]);
        rects.push_back(r); // Add rectangle to vector

        getline(cin, line);
    }

    // Exit if user didn't enter any lines
    if(rects.size() == 0) return -1;

    // Loop while there are still rectangles that overlap
    while(rects.size() > 1){

        Rect n = rects[0]; // Current rectangle
        // Test if last rectangle fits inside the first one
        if(!n.combine(rects.back())){
            // Test if first rectangle fits inside the last one
            n = rects.back();
            if(!n.combine(rects[0])){
                // Rectangles don't overlap
                cout << "0" << endl;
                return 0;
            }
        }

        //Rectangles overlap
        rects[0] = n; // Save combined rectangles over old one
        rects.pop_back(); // Remove other from vector


    }

    // Output area
    cout << rects[0].getArea() << endl;

    return 0;
}

/* Split Line
 * Split a line at spaces and commas
 * Convert each section to a double and save results in an array */
void SplitLine(string line, double (&result)[4]){

    string nums[4]; // Split strings

    // Split line
    for(int i = 0, n = 0; line[i] && n < 4; i++){
        if(line[i] == ' ' || line[i] == ',') n++;
        else nums[n] += line[i];
    }

    // Convert numbers
    for(int i = 0; i < 4; i++){
        result[i] = stod(nums[i]);
    }

}