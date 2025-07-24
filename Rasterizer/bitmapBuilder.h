#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <iostream>
#include <fstream>

/**
* @brief A RGB color with values between 0 and 255
*/
struct Color {
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
};

/**
* @class BMP
* @brief Stores an array of colors and writes them into a BMP file
*/
class BMP {
	char * filepath = nullptr;
	int width = 0;
	int height = 0;
	Color** colormap = nullptr;

	void WriteHeader(std::ofstream& file);
	void WritePixels(std::ofstream& file);
	bool openFile(std::ofstream& out);
public:
	/**
	* @brief Creates a empty BMP object without a file path, size or initialized pixel array
	*/
	BMP();
	/**
	* @brief Creates a BMP object that contains an image, sets output path to path, set pixel array dimensions to width and height
	* @param path The path to the output file to use when writing
	* @param width The width of the pixel array
	* @param height The Height of the pixel array
	*/
	BMP(const char* path, int width, int height);
	/**
	* @brief Creates a BMP object that contains an image and sets output path to path
	* @param path The path to the output file to use when writing
	*/
	BMP(const char* path);
	~BMP();

	/**
	* @brief Sets the dimensions of the pixel array
	* @param width The width of the new pixel array
	* @param height The height of the new pixel array
	*/
	void SetSize(int width, int height);
	/**
	* @brief Sets the output file path
	* @param path The new output file path
	*/
	void SetFilepath(const char* path);

	/**
	* @brief Gets the width of the pixel array
	* @return The width in pixels
	*/
	int GetWidth() { return width; }
	/**
	* @brief Gets the height of the pixel array
	* @return The height in pixels
	*/
	int GetHeight() { return height; }

	/**
	* @brief Attempts to write pixel array into filepath
	* @return If the function was successful
	*/
	bool WriteToFile();

	/**
	* @brief Gets a color at (x,y) in the pixel array
	* @param x The x value of the pixel starting from the left of the image
	* @param y The y value of the pixel start from the bottom of the image
	*/
	Color& at(int x, int y);

	/**
	* @brief Sets the color of pixel in the pixel array at (x,y)
	* @param x The x value of the pixel starting from the left of the image
	* @param y The y value of the pixel start from the bottom of the image
	* @param color The color of the pixel
	*/
	void Set(int x, int y, Color color);
	/**
	* @brief Sets the color of pixel in the pixel array at (x,y)
	* @param x The x value of the pixel starting from the left of the image
	* @param y The y value of the pixel start from the bottom of the image
	* @param red The red intensity of the pixel
	* @param green The green intensity of the pixel
	* @param blue The blue intensity of the pixel
	*/
	void Set(int x, int y, uint8_t red, uint8_t green, uint8_t blue);


	/**
	* @brief Fills pixel array with color
	* @param color The color to fill
	*/
	void Fill(Color color);

};

std::ostream& operator<<(std::ostream& stream, const Color& pixel);