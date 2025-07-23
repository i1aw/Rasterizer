#include "rasterizer.h"

void Rasterizer::DrawTriangle(Triangle2D triangle, Color color) {
	
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