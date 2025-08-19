#include "bitmapBuilder.h"
#include "rasterizer.h"
#include "projector.h"
#include "window.h"
#include "RenderTarget.h"

using namespace std;

int main() {
	const int width = 1920;
	const int height = 1080;
	//const int width = 4;
	//const int height = 4;

	Rasterizer r("output.bmp", width, height);
	ProjectorCamera cam({ 0,0,-2 }, 80, width, height);
	Window w(width, height, "Rasterizer");
	Target tar(width, height);
	//Triangle3D triangle({ 10,10,1 }, { 900,900, 1 }, { 1000,10,1 });
	Triangle3D triangle({ -0.5,-0.5,1 }, { 0.5,0.5, 1 }, { 0.5,-0.5,1 });

	RGBColor red = { 255, 0, 0 };
	
	while (!WindowShouldClose()) {

		BeginDrawing();
		r.DrawTriangle(tar, cam.ProjectTo2D(triangle), red);
		cout << tar.texture;
		w.Update(tar);
		EndDrawing();
	}

	return 0;
}