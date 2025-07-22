#include "rasterizer.h"

void Vector::Perp() {
	int temp = 0;

	temp = start.x;
	start.x = -start.y;
	start.y = temp;

	temp = end.x;
	end.x = -end.y;
	end.y = temp;

}

Point Vector::GetDelta() const {
	Point delta = {
		end.x - start.x,
		end.y - start.y
	};
	return delta;
}

double Vector::operator*(Vector other) {
	Point delta = GetDelta();
	Point otherDelta = other.GetDelta();
	return (delta.x * otherDelta.x) + (delta.y * otherDelta.y);
}

bool Vector::PointOnRight(Point p) const {
	Vector toP(start, p);
	toP.Perp();
	return 0 <= toP * *this;
}

Vector::Vector() {
	;
}

bool Triangle::PointInTriangle(Point p) {
	return lines[0].PointOnRight(p) 
		&& lines[1].PointOnRight(p) 
		&& lines[2].PointOnRight(p);
}

Triangle::Triangle() {
	;
}

Triangle::Triangle(Point A, Point B, Point C) {
	lines[0] = Vector(A, B);
	lines[1] = Vector(B, C);
	lines[2] = Vector(C, A);
}

void Rasterizer::DrawTriangle(Triangle t, Color c) {
	for (int x = 0; x < image.GetWidth(); x++) {
		for (int y = 0; y < image.GetHeight(); y++) {
			Point currentPixel = { x,y };
			if (t.PointInTriangle(currentPixel)) {
				image.at(x, y) = c;
			}
		}
	}
}