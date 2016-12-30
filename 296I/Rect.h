//
// Created by matthew on 27/12/16.
//

#ifndef INTERCETINGRECTANGLES_RECT_H
#define INTERCETINGRECTANGLES_RECT_H



struct Point{
    double x;
    double y;
};


class Rect {
private:
    double area;
    Point points[4];
    void build(Point p1, Point p2);
    bool pointInside(Point p);
public:
    Rect(double x1, double y1, double x2, double y2);

    bool combine(Rect r2);
    void getPoints(Point (&arr)[4]);
    double getArea();
};


#endif //INTERCETINGRECTANGLES_RECT_H
