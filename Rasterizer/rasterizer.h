#pragma once
#include <iostream>
#include "bitmapBuilder.h"
#include "Geometry2D.h"

/**
* @class Rasterizer
* @brief contains a pixel array BMP object, lets the user draw shapes into the BMP object's pixel array
*/
class Rasterizer {
public:

	/**
	* @brief Constructs a Rasterizer with an output file path, width, and height
	* @param filepath The path to output renderer images to
	* @param width Output image width
	* @param height Output image height
	*/
	Rasterizer(const char* filepath, int width, int height) : image(filepath, width, height) {};

	/**
	* @brief BMP object used to store and output renders
	*/
	BMP image;

	/**
	* Set all pixels within triangle to color
	*
	* @param triangle 2D triangle object to draw
	* @param color RGB color to use
	*
	*/
	void DrawTriangle(Triangle2D t, Color c);
};