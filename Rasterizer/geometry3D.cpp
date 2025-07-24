#include "geometry3D.h"

Triangle3D::Triangle3D(Point3D A, Point3D B, Point3D C) {
	vertexes[0] = A;
	vertexes[1] = B;
	vertexes[2] = C;
}

Point3D operator+(Point3D a, Point3D b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Point3D operator-(Point3D a, Point3D b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}