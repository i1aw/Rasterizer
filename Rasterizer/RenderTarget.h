#pragma once
#include "constants.h"

class Target {
	static const int PIXEL_SIZE = 4;

public:
	int width;
	int height;

	// width first flattened 2d array
	unsigned char* texture = nullptr;
	Target(int width, int height);
	~Target();
	void Fill(RGBColor c);
	void SetColor(unsigned char*& location, RGBColor c);
	void SkipPixel(unsigned char*& location);
	void SkipPixel(unsigned char*& location, int amount);

};