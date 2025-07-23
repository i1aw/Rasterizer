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
	;
}

bool Triangle2D::PointInTriangle(Point2D p) {
	return lines[0].PointOnRight(p)
		&& lines[1].PointOnRight(p)
		&& lines[2].PointOnRight(p);
}

Triangle2D::Triangle2D() {
	;
}

Triangle2D::Triangle2D(Point2D A, Point2D B, Point2D C) {
	lines[0] = Vector2D(A, B);
	lines[1] = Vector2D(B, C);
	lines[2] = Vector2D(C, A);
}