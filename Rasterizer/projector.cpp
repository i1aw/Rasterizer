#include "projector.h"
#include <cmath>

Point2D ProjectorCamera::ProjectTo2D(Point3D point) {

	double fovRadians = fov * (3.14159265 / 180.0);

	double scale = tan(fovRadians / 2) * 2;

	Point2D centerOffset = { width / 2, height / 2 };

	Point3D projPoint3D = point;

	projPoint3D = projPoint3D - position;

	Point2D projPoint2D = { projPoint3D.x, projPoint3D.y };

	// account for center offset
	projPoint2D = projPoint2D - centerOffset;

	// do projection assuming focal length is 1
	projPoint2D.x /= projPoint3D.z;
	projPoint2D.y /= projPoint3D.z;

	// correct for FOV
	projPoint2D = projPoint2D / scale;
	
	projPoint2D = projPoint2D + centerOffset;
	

	return projPoint2D;
}

Triangle2D ProjectorCamera::ProjectTo2D(Triangle3D triangle) {
	Triangle2D projTriangle;

	for (int i = 0; i < 3; i++) {
		projTriangle.vertexes[i] = ProjectTo2D(triangle.vertexes[i]);
	}

	return projTriangle;
}
