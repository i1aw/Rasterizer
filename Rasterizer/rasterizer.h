#pragma once
#include <iostream>
#include "bitmapBuilder.h"

struct Point {
	int x = 0;
	int y = 0;
};

class Vector {
	Point start;
	Point end;

public:

	Vector();
	Vector(Point s, Point e) : start(s), end(e) {};
	Vector(Point delta) : end(delta) {};
	Point SetStart(Point p) { start = p; }
	Point SetEnd(Point p) { end = p; }
	Point GetStart() const { return start; }
	Point GetEnd() const { return end; }
	Point GetDelta() const;
	bool PointOnRight(Point p) const;
	void Perp();
	double operator*(Vector other);
	
};

class Triangle {
	
public:
	Triangle();
	Triangle(Point A, Point B, Point C);
	Vector lines[3];
	bool PointInTriangle(Point point);
};

class Rasterizer {
public:
	Rasterizer(const char* filepath, int width, int height) : image(filepath, width, height) {};
	BMP image;
	void DrawTriangle(Triangle t, Color c);
};