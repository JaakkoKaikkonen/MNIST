#pragma once

#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace engine {

	class ImageReader
	{
	public:
		ImageReader(gameDataRef data, const char* imageFilename, const char* labelFilename, int numOfImages);
		~ImageReader();

		void loadNext();

		void drawCurrent();

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

		const int w = 28;

		//Scale must be odd number
		int scale = 7;

		sf::RectangleShape pixel;

	};

}

