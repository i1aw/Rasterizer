#include "geometry2D.h"

Point2D operator-(Point2D a, Point2D b) {
	return { a.x - b.x, a.y - b.y};
}

Point2D operator+(Point2D a, Point2D b) {
	return { a.x + b.x, a.y + b.y };
}

Point2D operator*(double a, Point2D b) {
	return { (a * b.x), (a * b.y) };
}

Point2D operator*(Point2D a, double b) {
	return { (b * a.x), (b * a.y) };
}

Point2D operator/(double a, Point2D b) {
	return { (b.x / a), (b.y / a) };
}

Point2D operator/(Point2D a, double b) {
	return { (a.x / b), (a.y / b) };
}

void Vector2D::Perp() {
	double temp = 0;

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

	startX = std::min(std::min(A.x, B.x), C.x);
	startY = std::min(std::min(A.y, B.y), C.y);
	endX = std::max(std::max(A.x, B.x), C.x);
	endY = std::max(std::max(A.y, B.y), C.y);
}

void Triangle2D::UpdateBounds() {
	Point2D A = vertexes[0];
	Point2D B = vertexes[1];
	Point2D C = vertexes[2];

	startX = std::min(std::min(A.x, B.x), C.x);
	startY = std::min(std::min(A.y, B.y), C.y);
	endX = std::max(std::max(A.x, B.x), C.x);
	endY = std::max(std::max(A.y, B.y), C.y);
}