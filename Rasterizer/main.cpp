#include "bitmapBuilder.h"
#include "rasterizer.h"
#include "projector.h"

using namespace std;

int main() {

	const Color black = { 0,0,0 };
	const Color red = { 200,25,25 };
	Camera cam({ 0,0,0 }, 30, 1920, 1080);
	Rasterizer r("30fov.bmp", 1920, 1080);

	Triangle3D triangle({ 10,10,1 }, { 900,900, 1 }, { 1000,10,1 });
	r.DrawTriangle(cam.ProjectTo2D(triangle), red);
	r.image.WriteToFile();

	cam.fov = 60.0;
	r.image.Fill(black);
	r.DrawTriangle(cam.ProjectTo2D(triangle), red);
	r.image.SetFilepath("60fov.bmp");
	r.image.WriteToFile();

	cam.fov = 90;
	r.image.Fill(black);
	r.DrawTriangle(cam.ProjectTo2D(triangle), red);
	r.image.SetFilepath("90fov.bmp");
	r.image.WriteToFile();

	return 0; // TEMP
}