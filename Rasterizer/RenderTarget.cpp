#include "RenderTarget.h"

Target::Target(int width = 0, int height = 0) {
	this->width = width;
	this->height = height;

	this->texture = new unsigned char[this->width * this->height * PIXEL_SIZE];
}

Target::~Target() {
	if (texture) {
		delete[] texture;
	}
}

void Target::Fill(RGBColor c) {
	for (int i = 0; i < width * height * PIXEL_SIZE; i += PIXEL_SIZE) {
		texture[i + 0] = c.red;
		texture[i + 1] = c.green;
		texture[i + 2] = c.blue;
		texture[i + 3] = (unsigned char)255;
	}
}

void Target::SetColor(unsigned char*& location, RGBColor c) {
	*location = c.red;
	location++;
	*location = c.green;
	location++;
	*location = c.blue;
	location++;
	*location = 255u;
	location++;
}

void Target::SkipPixel(unsigned char*& location) {
	location += PIXEL_SIZE;
}

void Target::SkipPixel(unsigned char*& location, int amount) {
	location += PIXEL_SIZE * amount;
}