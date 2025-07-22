#include "bitmapBuilder.h"
#include "rasterizer.h"

using namespace std;

int main() {
	const Color red = {255,0,0};
	Triangle t1({10,10}, {900,900}, {500,10});
	cout << "starting...\n";

	Rasterizer r("output.bmp", 1920, 1080);
	//image.Set(1, 1, red);
	r.DrawTriangle(t1, red);
	r.image.WriteToFile();

	cout << "done.\n";
	
	return 0;
}