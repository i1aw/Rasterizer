#include "rasterizer.h"
#include "window.h"
#include "RenderTarget.h"

void Rasterizer::DrawTriangle(Triangle2D triangle, RGBColor color) {
	
	// TODO: only iterated over the bounding box of the triangle
	for (int x = 0; x < image.GetWidth(); x++) {
		for (int y = 0; y < image.GetHeight(); y++) {
			Point2D currentPixel = { x,y };
			if (triangle.PointInTriangle(currentPixel)) {
				image.at(x, y) = color;
			}
		}
	}
}

void Rasterizer::DrawTriangle(Window window, Triangle2D triangle, RGBColor color) {
	window.Fill({ 0,0,0 });
	// TODO: only iterated over the bounding box of the triangle
	for (int x = 0; x < image.GetWidth(); x++) {
		for (int y = 0; y < image.GetHeight(); y++) {
			Point2D currentPixel = { x,y };
			if (triangle.PointInTriangle(currentPixel)) {
				window.SetPixel(x, y, color);
			}
		}
	}
}

void Rasterizer::DrawTriangle(Target& texture, Triangle2D triangle, RGBColor color) {
	// TODO: only iterated over the bounding box of the triangle

	texture.Fill({ 0,0,0 });
	unsigned char* texturePointer = texture.texture;

	for (int y = image.GetHeight() - 1; y >= 0; y--) {
		for (int x = 0; x < image.GetWidth(); x++) {
			Point2D currentPixel = { x,y };
			if (triangle.PointInTriangle(currentPixel)) {
				texture.SetColor(texturePointer, color);
			}
			else {
				texture.SkipPixel(texturePointer);
			}
		}
	}
}

