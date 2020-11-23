#pragma once

#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Matrix.h"

namespace engine {

	class ImageReader
	{
	public:
		ImageReader(gameDataRef data, const char* imageFilename, const char* labelFilename, const int numOfImages, const int imageWidth);
		~ImageReader();

		void loadNext();

		void drawCurrent(const int& scale);

		Matrix<float> currentImageToInputMatrix();

	public:

		char* currentImage;

		int label;

	private:

		gameDataRef data;

		struct ImageFileHeader {
			int magicNumber;
			int numberOfImages;
			int numberOfRows;
			int numberOfColumns;
		};

		ImageFileHeader imageFileHeader;

		struct LabelFileHeader {
			int magicNumber;
			int numberOfItems;
		};

		LabelFileHeader labelFileHeader;


		std::ifstream imageStream;
		std::ifstream labelStream;

		int numOfImages;
		int imageIndex = 1;

		const int width;

		sf::RectangleShape pixel;

	};

}

