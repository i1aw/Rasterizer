#pragma once
#include <iostream>

/**
* @brief A 2D coordinate point
*/
struct Point2D {
	double x = 0;
	double y = 0;
};

Point2D operator-(Point2D a, Point2D b);
Point2D operator+(Point2D a, Point2D b);
Point2D operator*(double a, Point2D b);
Point2D operator*(Point2D a, double b);
Point2D operator/(double a, Point2D b);
Point2D operator/(Point2D a, double b);

/**
* @class Vector2D
* @brief Contains a start and end point
*/
class Vector2D {
	Point2D start;
	Point2D end;

public:

	/**
	* @brief Default constructor, defines a vector with a start and end point at 0,0
	*/
	Vector2D();
	/**
	* @brief Creates a vector with a start and and end point
	* @param s Start point
	* @param e End point
	*/
	Vector2D(Point2D s, Point2D e) : start(s), end(e) {};
	/**
	* @brief Creates a displacement vector with an end point at delta
	* @param delta end point of the vector
	*/
	Vector2D(Point2D delta) : end(delta) {};
	/**
	* @brief Sets the start point of the vector
	* @param p New start point
	*/
	Point2D SetStart(Point2D p) { start = p; }
	/**
	* @brief Sets the end point of the vector
	* @param p New end point
	*/
	Point2D SetEnd(Point2D p) { end = p; }
	/**
	* @brief Gets the start point of the vector
	* @return start point
	*/
	Point2D GetStart() const { return start; }
	/**
	* @brief Gets the end point of the vector
	* @return end point
	*/
	Point2D GetEnd() const { return end; }
	/**
	* @brief Gets the displacement of the vector from start to end
	* @return Returns a displacement point
	*/
	Point2D GetDelta() const;
	/** @brief calculates if point p is on the right side of the vector
	* @param p The point to check
	* @return if the point is on the right
	*/
	bool PointOnRight(Point2D p) const;
	/**
	* @brief Rotates vector 90 degrees counterclockwise to make it perpendicular to the original vector
	*/
	void Perp();
	double operator*(Vector2D other);
	bool operator==(Vector2D other);

};

/**
* @class Triangle2D
* @brief A 2D triangle
*/
class Triangle2D {
	Vector2D prevVectors[3];
	bool initialCalculation = false;

	Vector2D vectors[3];

	void CalculateVectors();
public:
	/**
	* @brief Creates a triangle
	*/
	Triangle2D();

	/**
	* @brief Creates a triangle made of the points A, B, and C
	* @param A The first point of the triangle
	* @param B the second point of the triangle
	* @param C the third point of the triangle
	* @note for compatibility with rasterizer, initialize A, B, and C clockwise
	*/
	Triangle2D(Point2D A, Point2D B, Point2D C);

	/**
	* @brief Returns if a point is in a triangle
	* @param point The point to check
	* @return Returns if the point is in the triangle
	*/
	bool PointInTriangle(Point2D point);

	/**
	* @brief The vertexes that make up the triangle
	*/
	Point2D vertexes[3];

};