#pragma once
#include <iostream>

struct Point2D {
	int x = 0;
	int y = 0;
};

class Vector2D {
	Point2D start;
	Point2D end;

public:

	Vector2D();
	Vector2D(Point2D s, Point2D e) : start(s), end(e) {};
	Vector2D(Point2D delta) : end(delta) {};
	Point2D SetStart(Point2D p) { start = p; }
	Point2D SetEnd(Point2D p) { end = p; }
	Point2D GetStart() const { return start; }
	Point2D GetEnd() const { return end; }
	Point2D GetDelta() const;
	bool PointOnRight(Point2D p) const;
	void Perp();
	double operator*(Vector2D other);

};

class Triangle2D {

public:
	Triangle2D();
	Triangle2D(Point2D A, Point2D B, Point2D C);
	Vector2D lines[3];
	bool PointInTriangle(Point2D point);
};