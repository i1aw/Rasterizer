#pragma once
#include <iostream>
#include "bitmapBuilder.h"
#include "Geometry2D.h"
#include "window.h"
#include "RenderTarget.h"
#include "geometry3D.h"
#include "projector.h"

/**
* @class Rasterizer
* @brief contains a pixel array BMP object, lets the user draw shapes into the BMP object's pixel array
*/
class Rasterizer {
public:

	Rasterizer();

	/**
	* @brief Constructs a Rasterizer with an output file path, width, and height
	* @param filepath The path to output renderer images to
	* @param width Output image width
	* @param height Output image height
	*/
	//Rasterizer(const char* filepath, int width, int height) : image(filepath, width, height) {};

	/**
	* @brief BMP object used to store and output renders
	*/
	//BMP image;

	/**
	* Set all pixels within triangle to color
	*
	* @param triangle 2D triangle object to draw
	* @param color RGB color to use
	*
	*/
	//void DrawTriangle(Triangle2D t, RGBColor c);

	/**
	* Set all pixels within triangle to color
	*
	* @param window The window to draw too
	* @param triangle 2D triangle object to draw
	* @param color RGB color to use
	*
	*/
	//void DrawTriangle(Window window, Triangle2D triangle, RGBColor color);

	void DrawTriangle(Target& texture, Triangle2D triangle, RGBColor color);

	void DrawCollection(Target& texture, Collection & obj, ProjectorCamera & cam, RGBColor color);
};