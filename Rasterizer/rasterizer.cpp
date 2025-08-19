#include "rasterizer.h"
#include "window.h"
#include "RenderTarget.h"

void Rasterizer::DrawTriangle(Triangle2D triangle, RGBColor color) {

	for (int x = 0; x < image.GetWidth(); x++) {
		for (int y = 0; y < image.GetHeight(); y++) {
			Point2D currentPixel = { (double)x,(double)y };
			if (triangle.PointInTriangle(currentPixel)) {
				image.at(x, y) = color;
			}
		}
	}
}

void Rasterizer::DrawTriangle(Window window, Triangle2D triangle, RGBColor color) {
	window.Fill({ 0,0,0 });

	int startX = std::max(triangle.getMinX(), 0);
	int endX = std::min(triangle.getMaxX(), image.GetWidth());
	int startY = std::max(triangle.getMinY(), 0);
	int endY = std::min(triangle.getMaxY(), image.GetHeight());

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {
			Point2D currentPixel = { (double)x,(double)y };
			if (triangle.PointInTriangle(currentPixel)) {
				window.SetPixel(x, y, color);
			}
		}
	}
}

void Rasterizer::DrawTriangle(Target& texture, Triangle2D triangle, RGBColor color) {
	texture.Fill({ 0,0,0 });
	unsigned char* texturePointer = texture.texture;

	int startX = std::max(triangle.getMinX(), 0);
	int endX = std::min(triangle.getMaxX(), image.GetWidth());
	int startY = std::max(triangle.getMinY(), 0);
	int endY = std::min(triangle.getMaxY(), image.GetHeight());

	// skip to first row with triangle
	texture.SkipPixel(texturePointer, startY * image.GetWidth());

	for (int y = endY - 1; y >= startY; y--) {

		// skip to get to the first column
		texture.SkipPixel(texturePointer, startX);
		for (int x = startX; x < endX; x++) {
			Point2D currentPixel = { (double)x,(double)y };
			if (triangle.PointInTriangle(currentPixel)) {
				texture.SetColor(texturePointer, color);
			}
			else {
				texture.SkipPixel(texturePointer);
			}
		}

		for (int i = endX; i < image.GetWidth(); i++) {
			texture.SkipPixel(texturePointer);
		}
	}
}

