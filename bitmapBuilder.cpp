#include "bitmapBuilder.h"

BMP::BMP(const char* path, int width, int height) {
	SetSize(width, height);
	SetFilepath(path);
}

BMP::BMP(const char* path) {
	SetFilepath(path);
}

BMP::BMP() {
	;
}

BMP::~BMP() {
	if (filepath != nullptr)
		delete[] filepath;

	if (colormap != nullptr) {
		for (int i = 0; i < width; i++) {
			delete[] colormap[i];
		}

		delete[] colormap;
	}
}

void BMP::SetSize(int width, int height) {
	this->width = width;
	this->height = height;
	if (colormap != nullptr) {
		for (int i = 0; i < width; i++) {
			delete[] colormap[i];
		}

		delete[] colormap;
		
	}

	colormap = new Color*[width];

	for (int i = 0; i < width; i++) {
		colormap[i] = new Color[height];
	}
}

void BMP::SetFilepath(const char* filepath) {
	if (this->filepath != nullptr)
		delete[] this->filepath;

	this->filepath = new char[strlen(filepath) + 1];
	strcpy(this->filepath, filepath);
}

Color& BMP::at(int x, int y) {
	if (colormap != nullptr) {
		return colormap[x][y];
	}
}

void BMP::Set(int x, int y, Color p) {
	if (colormap != nullptr) {
		colormap[x][y] = p;
	}
}

void BMP::Set(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
	if (colormap != nullptr) {
		colormap[x][y].red = red;
		colormap[x][y].green = green;
		colormap[x][y].blue = blue;
	}
}

std::ostream& operator<<(std::ostream& stream, const Color& pixel) {
	stream << '(' << (int)pixel.red << ", " << (int)pixel.green << ", " << (int)pixel.blue << ")\n";
	return stream;
}

// code to write bmp to file:

// made with help from https://stackoverflow.com/a/47785639
void BMP::WriteHeader(std::ofstream& file) {
	int filesize = 3 * width * height; // rgb channels WxH
	static const int INFO_HEADER_SIZE = 40;
	static const int HEADER_SIZE = 14;

	// header
	static char BMPHeader[HEADER_SIZE + 1] = {
		0, 0,       // signature
		0, 0, 0, 0, // image size
		0, 0, 0, 0, // unused
		0, 0, 0, 0, // start offset
	};
	
	BMPHeader[0] = (char)'B';
	BMPHeader[1] = (char)'M';
	BMPHeader[2] = (char)(filesize >> 8 * 0);
	BMPHeader[3] = (char)(filesize >> 8 * 1);
	BMPHeader[4] = (char)(filesize >> 8 * 2);
	BMPHeader[5] = (char)(filesize >> 8 * 3);
	BMPHeader[10] = (char)(INFO_HEADER_SIZE + HEADER_SIZE);

	// info header
	static char BMPHeaderInfo[INFO_HEADER_SIZE + 1] = {
		0,0,0,   // info header size
		0,0,0,0, // image width
		0,0,0,0, // image height
		0,0,     // color plane count
		0,0,     // bits / pixel
		0,0,0,   // compression
		0,0,0,0, // image size
		0,0,0,0, // horizontal p/m
		0,0,0,0, // vertical p/m
		0,0,0,0, // color table colors count
		0,0,0,0, // important color count
	};

	BMPHeaderInfo[0] = (char)(INFO_HEADER_SIZE); // info header size

	BMPHeaderInfo[4] = (char)(width >> 8 * 0);   // width
	BMPHeaderInfo[5] = (char)(width >> 8 * 1);
	BMPHeaderInfo[6] = (char)(width >> 8 * 2);
	BMPHeaderInfo[7] = (char)(width >> 8 * 3);

	BMPHeaderInfo[8] = (char)(height >> 8 * 0);  // height
	BMPHeaderInfo[9] = (char)(height >> 8 * 1);
	BMPHeaderInfo[10] = (char)(height >> 8 * 2);
	BMPHeaderInfo[11] = (char)(height >> 8 * 3);

	BMPHeaderInfo[12] = (char)(1);               // color planes

	BMPHeaderInfo[14] = (char)(8 * 3);           // bits per pixel

	file.write(BMPHeader, HEADER_SIZE);
	file.write(BMPHeaderInfo, INFO_HEADER_SIZE);
}

void BMP::WritePixels(std::ofstream& file) {
	int paddingBytes = (4 - (width * 3) % 4) % 4;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Color current = at(x, y);
			char color[3] = {
				(char)(current.blue),
				(char)(current.green),
				(char)(current.red)
			};
			file.write(color, 3);
		}
		// padding
		for (int i = 0; i < paddingBytes; i++) {
			file.write("\0", 1);
		}
		
	}
}

bool BMP::openFile(std::ofstream& out) {
	if (filepath == nullptr)
		return false;
	out.open(filepath);
	return out.is_open();
}

bool BMP::WriteToFile() {
	std::ofstream file;
	if (!openFile(file))
		return false;
	if (colormap == nullptr)
		return false;

	WriteHeader(file);
	WritePixels(file);
	file.close();

	return true;
}