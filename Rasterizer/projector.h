#pragma once
#include "geometry3D.h"
#include "geometry2D.h"

class Camera {
public:

	/** 
	* @brief Constructs a new Camera object
	*/
	Camera() {};

	/**
	* @brief Constructs a new Camera object
	* @param position The 3D position of the Camera
	*/
	Camera(Point3D position) : position(position) {};

	/**
	* @brief Constructs a new Camera object
	* @param position The 3D position of the Camera
	* @param fov The field of view of the Camera
	*/
	Camera(Point3D position, double fov) : 
		position(position), 
		fov(fov) 
	{};

	/**
	* @brief Constructs a new Camera object
	* @param position The 3D position of the Camera
	* @param fov The field of view of the Camera
	* @param width The width of the output image
	* @param height The height of the output image
	*/
	Camera(Point3D position, double fov, int width, int height) :
		position(position),
		fov(fov),
		width(width),
		height(height)
	{};


	/**
	* @brief The position of the camera in 3D space
	*/
	Point3D position;

	/** 
	* @brief The field of view of the camera
	*/
	double fov = 60.0;

	/**
	* @brief The width of the output image
	*/
	int width = 32;

	/**
	* @brief The height of the output image
	*/
	int height = 32;

	/**
	* @brief Projects a 3D point into 2D
	* @param point The input point
	* @return The 3D point projected to 2D
	*/
	Point2D ProjectTo2D(Point3D point);

	/**
	* @brief Projects a 3D triangle into a 2D triangle
	* @param triangle The input triangle
	* @return The 3D triangle projected to 2D
	*/
	Triangle2D ProjectTo2D(Triangle3D triangle);
};