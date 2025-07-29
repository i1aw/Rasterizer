#pragma once
#include "Geometry2D.h"
#include <raylib.h>
#include "constants.h"
#include "RenderTarget.h"

class Window {
public:
	int width;
	int height;
	Color backgroundColor = BLACK;
	Texture2D texture; 
	unsigned char* textureBytes = nullptr;

	Window(int width, int height, const char* title);
	~Window();
	void Update();
	void Update(Target& newTexture);
	void TestTexture();
	void SetPixel(int x, int y, RGBColor color);
	void Fill(RGBColor color);
};