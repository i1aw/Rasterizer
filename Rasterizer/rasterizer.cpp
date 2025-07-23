#include "rasterizer.h"

void Rasterizer::DrawTriangle(Triangle2D t, Color c) {
	
	for (int x = 0; x < image.GetWidth(); x++) {
		for (int y = 0; y < image.GetHeight(); y++) {
			Point2D currentPixel = { x,y };
			if (t.PointInTriangle(currentPixel)) {
				image.at(x, y) = c;
			}
		}
	}
}