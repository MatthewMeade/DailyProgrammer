/* Rect.cpp
 *
 * Represents a rectangle with four points for each corner
 */
#include "Rect.h"
#include <vector>

// Constructor
Rect::Rect(double x1, double y1, double x2, double y2){
    Point p1 = {x1, y1};
    Point p2 = {x2, y2};
    build(p1, p2);
}

/* Build
 * Given two points, calculates the other two points and area for the rectangle */
void Rect::build(Point p1, Point p2) {

    // Position p1 on the left
    if(p1.x > p2.x){
        double tmp = p1.x;
        p1.x = p2.x;
        p2.x = tmp;
    }

    // Position p1 on the bottom
    if(p1.y > p2.y){
        double tmp = p1.y;
        p1.y = p2.y;
        p2.y = tmp;
    }

    // Assign points to array
    points[0] = (Point){p1.x, p2.y}; // Top Left
    points[1] = p2; // Top Right
    points[2] = p1; // Bottom Left
    points[3] = (Point){p2.x, p1.y}; // Bottom right

    // area = length * height
    area = (p2.x - p1.x) * (p2.y - p1.y);

}

/* Combine
 * Takes in a second rectangle
 *
 * Re builds current rectangle so that it
 * is equal to the intersection area of both rectangles
 *
 * If rectangles don't overlap, returns false */
bool Rect::combine(Rect r2) {
    // Parallel vectors
    std::vector <Point> intPoints; // Points inside rectangle
    std::vector <int> pointNums; // Point index

    // Points of second rectangle
    Point points2[4];
    r2.getPoints(points2);

    // Loop through the points of rectangle two and determine what ones
    // are within the range of the current rectangle
    for(int i = 0; i < 4; i++){
        if(pointInside(points2[i])){
            intPoints.push_back(points2[i]);
            pointNums.push_back(i);
        }
    }

    // No points are nested in current rectangle
    // Rectangles either cross or don't overlap
    if(intPoints.size() == 0){
        // If points exist on both sides of the rectangle they must cross
        if(points2[0].y > points[0].y && points2[2].y < points[2].y){
            build((Point){points2[0].x, points[2].y}, (Point){points2[1].x, points[0].y});
        }else return false; // If not, they don't overlap
    }

    // One point is nested inside current rectangle
    if(intPoints.size() == 1){
        build(intPoints[0], points[3-pointNums[0]]);
    }

    // Two points are nested inside current rectangle
    if(intPoints.size() == 2){

        // Test if rectangles overlap on a vertical side
        bool vert = intPoints[0].x == intPoints[1].x;

        // Calculate positions of intersection based on position of points
        int n = ((pointNums[0] == 1 || pointNums[1] == 1) != vert) ? 3 : 0;
        if(vert){
            build(intPoints[0], (Point){points[n].x, intPoints[1].y});
        }else{
            build(intPoints[0], (Point){intPoints[1].x, points[n].y});
        }
    }

    // All points are nested inside the current rectangle
    // The second rectangle is equal to the overlap
    if(intPoints.size() > 2){
        build(points2[0], points2[3]);
    }
    return true;

}

/* Point Inside
 * Determine if given point is inside the rectangle */
bool Rect::pointInside(Point p){
    if(p.x <= points[0].x || p.x >= points[1].x)return false; // Test if x is in range
    if(p.y <= points[2].y || p.y >= points[0].y)return false; // Test id y is in range
    return true;
}


// Accessor Methods

/* Get Area
 * Returns area of rectangle */
double Rect::getArea() {
    return area;
}

/* Get Points
 * Assign points array to array passed by reference */
void Rect::getPoints(Point (&arr)[4]){
    for(int i = 0; i < 4; i++){
        arr[i] = points[i];
    }
}