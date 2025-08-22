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
	const uint32_t packed = (uint32_t)c.red |
		((uint32_t)c.green << 8) |
		((uint32_t)c.blue << 16) |
		(0xFFu << 24);
	auto* p32 = reinterpret_cast<uint32_t*>(texture);
	const size_t count = (size_t)width * height;
	std::fill_n(p32, count, packed);  // one store per pixel
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