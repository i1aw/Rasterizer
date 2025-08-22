#include "bitmapBuilder.h"
#include "rasterizer.h"
#include "projector.h"
#include "window.h"
#include "RenderTarget.h"
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	const int width = 1920;
	const int height = 1080;
	double maxFPS = -1;

	cout << fixed << setprecision(2);

	Rasterizer r;
	ProjectorCamera cam({ 0,0,-4 }, 80, width, height);
	Window w(width, height, "Rasterizer", 1000000);
	Target tar(width, height);

	vector<Triangle3D> triangles;

	// Front (z = 1) — given (clockwise from outside, normals point inward)
	triangles.push_back(Triangle3D({ -0.5, -0.5, 1 }, { 0.5,  0.5, 1 }, { 0.5, -0.5, 1 }));
	triangles.push_back(Triangle3D({ -0.5, -0.5, 1 }, { -0.5,  0.5, 1 }, { 0.5,  0.5, 1 }));

	// Back (z = 0) — appears CCW from the front view, but is CW from behind
	triangles.push_back(Triangle3D({ -0.5, -0.5, 0 }, { 0.5, -0.5, 0 }, { 0.5,  0.5, 0 }));
	triangles.push_back(Triangle3D({ -0.5, -0.5, 0 }, { 0.5,  0.5, 0 }, { -0.5,  0.5, 0 }));

	// Right (x = 0.5), clockwise when viewed from +x
	triangles.push_back(Triangle3D({ 0.5, -0.5, 1 }, { 0.5,  0.5, 1 }, { 0.5,  0.5, 0 }));
	triangles.push_back(Triangle3D({ 0.5, -0.5, 1 }, { 0.5,  0.5, 0 }, { 0.5, -0.5, 0 }));

	// Left (x = -0.5), clockwise when viewed from -x
	triangles.push_back(Triangle3D({ -0.5, -0.5, 1 }, { -0.5,  0.5, 0 }, { -0.5,  0.5, 1 }));
	triangles.push_back(Triangle3D({ -0.5, -0.5, 1 }, { -0.5, -0.5, 0 }, { -0.5,  0.5, 0 }));

	// Top (y = 0.5), clockwise when viewed from +y
	triangles.push_back(Triangle3D({ -0.5,  0.5, 1 }, { -0.5,  0.5, 0 }, { 0.5,  0.5, 0 }));
	triangles.push_back(Triangle3D({ -0.5,  0.5, 1 }, { 0.5,  0.5, 0 }, { 0.5,  0.5, 1 }));

	// Bottom (y = -0.5), clockwise when viewed from -y
	triangles.push_back(Triangle3D({ -0.5, -0.5, 1 }, { 0.5, -0.5, 0 }, { -0.5, -0.5, 0 }));
	triangles.push_back(Triangle3D({ -0.5, -0.5, 1 }, { 0.5, -0.5, 1 }, { 0.5, -0.5, 0 }));

	Collection object;

	for (int i = 0; i < triangles.size(); i++) {
		object.AddFace(triangles[i]);
	}

	/*Point3D* vertexes = new Point3D[3];
	vertexes[0] = { -0.5,-0.5,1 };
	vertexes[1] = { 0.5,0.5, 1 };
	vertexes[2] = { 0.5,-0.5,1 };

	int** faces = new int*[1];
	faces[0] = new int[3];

	faces[0][0] = 0;
	faces[0][1] = 1;
	faces[0][2] = 2;

	/*Collection object(vertexes, 3, faces, 1);*/

	RGBColor triangleColor = { 123, 120, 126 };

	int direction = 1;

	while (!WindowShouldClose()) {
		auto start = chrono::high_resolution_clock::now();

		BeginDrawing();
		tar.Fill({ 212, 233, 252 });
		r.DrawCollection(tar, object, cam, triangleColor);
		w.Update(tar);
		auto end = chrono::high_resolution_clock::now();
		auto seconds = chrono::duration<double>(end - start);
		EndDrawing();

		if (direction > 0) {
			cam.position.y += 0.005;
		}
		else {
			cam.position.y -= 0.005;
		}

		if (cam.position.y >= 1.5) {
			direction = -1;
		}
		else if (cam.position.y <= -1.5) {
			direction = 1;
		}

		maxFPS = max(maxFPS, 1 / seconds.count());
		cout << "                    \r";
		cout << maxFPS << " max fps";
	}

	return 0;
}