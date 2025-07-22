#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <iostream>
#include <fstream>


struct Color {
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
};

class BMP {
	char * filepath = nullptr;
	int width = 0;
	int height = 0;
	Color** colormap = nullptr;

	void WriteHeader(std::ofstream& file);
	void WritePixels(std::ofstream& file);
	bool openFile(std::ofstream& out);
public:
	BMP();

public:
	// setters
	BMP(const char* path, int width, int height);
	BMP(const char* path);
	~BMP();

	void SetSize(int, int);
	void SetFilepath(const char*);

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	bool WriteToFile();

	Color& at(int x, int y);
	void Set(int x, int y, Color p);
	void Set(int x, int y, uint8_t red, uint8_t green, uint8_t blue);

};

std::ostream& operator<<(std::ostream& stream, const Color& pixel);