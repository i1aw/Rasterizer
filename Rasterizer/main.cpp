#include "bitmapBuilder.h"
#include "rasterizer.h"
#include "projector.h"
#include "window.h"
#include "RenderTarget.h"
#include <chrono>
#include <iomanip>

using namespace std;

int main() {
	const int width = 1920;
	const int height = 1080;

	Rasterizer r;
	ProjectorCamera cam({ 0,0,-2 }, 80, width, height);
	Window w(width, height, "Rasterizer", 60);
	Target tar(width, height);
	//Triangle3D triangle({ 10,10,1 }, { 900,900, 1 }, { 1000,10,1 });
	Triangle3D triangle({ -0.5,-0.5,1 }, { 0.5,0.5, 1 }, { 0.5,-0.5,1 });

	RGBColor red = { 255, 0, 0 };
	
	cout << fixed << setprecision(2);

	while (!WindowShouldClose()) {
		auto start = chrono::high_resolution_clock::now();

		BeginDrawing();
		r.DrawTriangle(tar, cam.ProjectTo2D(triangle), red);
		w.Update(tar);
		EndDrawing();

		auto end = chrono::high_resolution_clock::now();
		auto seconds = chrono::duration<double>(end - start);
		cout << "                    \r";
		cout << 1 / seconds.count() << " fps";
	}

	return 0;
}