#include "bitmapBuilder.h"
#include "rasterizer.h"
#include "projector.h"
#include "window.h"

using namespace std;

int main() {
	const int width = 1920;
	const int height = 1080;

	Rasterizer r("output.bmp", width, height);
	ProjectorCamera cam({ 0,0,0 }, 70, width, height);
	Window w(width, height, "First Window!");
	//Triangle3D triangle({ 10,10,1 }, { 900,900, 1 }, { 1000,10,1 });
	Triangle3D triangle({ -0.5,-0.5,1 }, { 0.5,0.5, 1 }, { 0.5,-0.5,1 });

	RGBColor red = { 255, 0, 0 };
	
	while (!WindowShouldClose()) {

		BeginDrawing();
		cam.fov += 1;
		cout << cam.fov << endl;
		r.DrawTriangle(w, cam.ProjectTo2D(triangle), red);
		w.Update();
		EndDrawing();
	}

	return 0;
}