#include "window.h"
#include "constants.h"
#include "RenderTarget.h"

Window::Window(int width = 600, int height = 400, const char* title="Unnamed Window") {
	this->width = width;
	this->height = height;
	InitWindow(width, height, title);

	if (textureBytes != nullptr) {
		delete[] textureBytes;
	}

	textureBytes = new unsigned char[width * height * 4];

	SetTargetFPS(60);

	texture = LoadTextureFromImage(GenImageColor(width, height, WHITE));
}

Window::~Window() {
	CloseWindow();
}

void Window::TestTexture() {
	for (int i = 0; i < width * height * 4; i += 4) {
		textureBytes[i]     = (unsigned char)255; // red
		textureBytes[i + 1] = (unsigned char)0;   // green
		textureBytes[i + 2] = (unsigned char)0;   // blue
		textureBytes[i + 3] = (unsigned char)255; // alpha

	}
}

void Window::SetPixel(int x, int y, RGBColor color) {
	int raylibX, raylibY;
	raylibX = height - y - 1;
	raylibY = x;

	int location = 4 * (raylibX * width + raylibY);
	textureBytes[location + 0] = color.red;
	textureBytes[location + 1] = color.green;
	textureBytes[location + 2] = color.blue;
	textureBytes[location + 3] = (unsigned char)255;

}

void Window::Fill(RGBColor color) {
	for (int i = 0; i < width * height * 4; i += 4) {
		textureBytes[i] = color.red;
		textureBytes[i + 1] = color.green;
		textureBytes[i + 2] = color.blue;
		textureBytes[i + 3] = (unsigned char)255;

	}
}

void Window::Update() {
	UpdateTexture(texture, textureBytes);
	DrawTexture(texture, 0, 0, WHITE);
}

void Window::Update(Target& newTexture) {
	UpdateTexture(texture, newTexture.texture);
	DrawTexture(texture, 0, 0, WHITE);
}