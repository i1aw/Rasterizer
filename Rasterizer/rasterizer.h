#pragma once
#include <iostream>
#include "bitmapBuilder.h"
#include "Geometry2D.h"

class Rasterizer {
public:
	Rasterizer(const char* filepath, int width, int height) : image(filepath, width, height) {};
	BMP image;
	void DrawTriangle(Triangle2D t, Color c);
};