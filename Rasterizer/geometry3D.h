#pragma once

/**
*  @brief a 3D coordinate point
*/
struct Point3D {
	int x = 0;
	int y = 0;
	int z = 0;
};

/**
* @class Triangle3D
* @brief A 3D triangle
*/
class Triangle3D {

public:

	/**
	* @brief Creates a triangle made of the points A, B, and C
	* @param A The first point of the triangle
	* @param B the second point of the triangle
	* @param C the third point of the triangle
	* @note for compatibility with rasterizer, initialize A, B, and C clockwise
	*/
	Triangle3D(Point3D A, Point3D B, Point3D C);

	/**
	* @brief The vertexes that make up the triangle
	*/
	Point3D vertexes[3];

};