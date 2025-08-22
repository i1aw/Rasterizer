#include "rasterizer.h"
#include "window.h"
#include "RenderTarget.h"

Rasterizer::Rasterizer() {
}

void Rasterizer::DrawTriangle(Target& texture, Triangle2D triangle, RGBColor color) {
	unsigned char* texturePointer = texture.texture;

	int startX = std::max(triangle.getMinX(), 0);
	int endX = std::min(triangle.getMaxX(), texture.width);
	int startY = std::max(triangle.getMinY(), 0);
	int endY = std::min(triangle.getMaxY(), texture.height);

	if (startX >= endX || startY >= endY) return;

	// skip to first row with triangle
	texture.SkipPixel(texturePointer, startY * texture.width);

	double deltaX_A = triangle.vertexes[1].x - triangle.vertexes[0].x;
	double deltaY_A = triangle.vertexes[1].y - triangle.vertexes[0].y;

	double deltaX_B = triangle.vertexes[2].x - triangle.vertexes[1].x;
	double deltaY_B = triangle.vertexes[2].y - triangle.vertexes[1].y;

	double deltaX_C = triangle.vertexes[0].x - triangle.vertexes[2].x;
	double deltaY_C = triangle.vertexes[0].y - triangle.vertexes[2].y;


	for (int y = startY; y < endY; y++) {

		// skip to get to the first column
		texture.SkipPixel(texturePointer, startX);

		double pointPerpX_A = (double)y - triangle.vertexes[0].y;
		double pointPerpX_B = (double)y - triangle.vertexes[1].y;
		double pointPerpX_C = (double)y - triangle.vertexes[2].y;

		for (int x = startX; x < endX; x++) {
			bool edge1 = false, edge2 = false, edge3 = false;
			
			double pointPerpY_A = -1 * ((double)x - triangle.vertexes[0].x);
			edge1 = deltaX_A * pointPerpX_A + deltaY_A * pointPerpY_A < 0;

			if (edge1) {
				double pointPerpY_B = -1 * ((double)x - triangle.vertexes[1].x);
				edge2 = deltaX_B * pointPerpX_B + deltaY_B * pointPerpY_B < 0;
			}
			
			if (edge2) {
				double pointPerpY_C = -1 * ((double)x - triangle.vertexes[2].x);
				edge3 = deltaX_C * pointPerpX_C + deltaY_C * pointPerpY_C < 0;
			}

			if (edge3) {
				texture.SetColor(texturePointer, color);
			}
			else {
				texture.SkipPixel(texturePointer);
			}
		}

		for (int i = endX; i < texture.width; i++) {
			texture.SkipPixel(texturePointer);
		}
	}
}

void Rasterizer::DrawCollection(Target& texture, Collection & obj, ProjectorCamera & cam, RGBColor color) {

	int faceCount = obj.GetFaceCount();
	for (int i = 0; i < faceCount; i++) {
		Triangle2D flattenFace = cam.ProjectTo2D(obj.GetFace(i));
		this->DrawTriangle(texture, flattenFace, color);
	}
}

