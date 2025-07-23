#include "geometry2D.h"

void Vector2D::Perp() {
	int temp = 0;

	temp = start.x;
	start.x = -start.y;
	start.y = temp;

	temp = end.x;
	end.x = -end.y;
	end.y = temp;

}

Point2D Vector2D::GetDelta() const {
	Point2D delta = {
		end.x - start.x,
		end.y - start.y
	};
	return delta;
}

double Vector2D::operator*(Vector2D other) {
	Point2D delta = GetDelta();
	Point2D otherDelta = other.GetDelta();
	return (delta.x * otherDelta.x) + (delta.y * otherDelta.y);
}

bool Vector2D::PointOnRight(Point2D p) const {
	Vector2D toP(start, p);
	toP.Perp();
	return 0 <= toP * *this;
}

Vector2D::Vector2D() {
}

bool Vector2D::operator==(Vector2D other) {
	return
		other.start.x == start.x &&
		other.start.y == start.y &&
		other.end.x   == end.x   &&
		other.end.y   == end.y;
}

void Triangle2D::CalculateVectors() {
	static Vector2D prevVectors[3];
	static bool initialCalculation = false;
	
	if (   
		initialCalculation &&
		prevVectors[0] == vectors[0] &&
		prevVectors[1] == vectors[1] &&
		prevVectors[2] == vectors[2]
		) 
	{
		return; 
	}
	initialCalculation = true;

	prevVectors[0] = vectors[0] = Vector2D(vertexes[0], vertexes[1]);
	prevVectors[1] = vectors[1] = Vector2D(vertexes[1], vertexes[2]);
	prevVectors[2] = vectors[2] = Vector2D(vertexes[2], vertexes[0]);
}

bool Triangle2D::PointInTriangle(Point2D p) {
	CalculateVectors();

	return vectors[0].PointOnRight(p)
		&& vectors[1].PointOnRight(p)
		&& vectors[2].PointOnRight(p);
}

Triangle2D::Triangle2D() {
}

Triangle2D::Triangle2D(Point2D A, Point2D B, Point2D C) {
	vertexes[0] = A;
	vertexes[1] = B;
	vertexes[2] = C;
}