#include "ImageReader.h"

namespace engine {

	ImageReader::ImageReader(gameDataRef data, const char* imageFilename, const char* labelFilename, int numOfImages)
		: data(data),
		  numOfImages(numOfImages)
	{
		pixel.setSize(sf::Vector2f(1, 1));

		currentImage = new char[w*w];

		//Image stream
		imageStream.open(imageFilename, std::ios::binary);

		if (!imageStream) {
			std::cout << "Error opening image file" << std::endl;
			return;
		}

		//??????????????????????????????????????????????????????
		imageStream.read(reinterpret_cast<char*>(&imageFileHeader), sizeof(imageFileHeader));

		//std::cout << "size(fileHeader): " << sizeof(imageFileHeader) << std::endl;
		
		//std::cout << imageFileHeader.magicNumber << std::endl;
		//std::cout << imageFileHeader.numberOfImages << std::endl;
		//std::cout << imageFileHeader.numberOfRows << std::endl;
		//std::cout << imageFileHeader.numberOfColumns << std::endl;
		//????????????????????????????????????????????????????


		//Label stream
		labelStream.open(labelFilename, std::ios::binary);

		if (!labelStream) {
			std::cout << "Error opening label file" << std::endl;
			return;
		}

		//????????????????????????????????????????????????????????????????????????
		labelStream.read(reinterpret_cast<char*>(&labelFileHeader), sizeof(labelFileHeader));

		//std::cout << labelFileHeader.magicNumber << std::endl;
		//std::cout << labelFileHeader.numberOfItems << std::endl;
		//?????????????????????????????????????????????????????????????????????????

		//Read first image
		imageStream.read(currentImage, w*w);

		//Read first label
		label = labelStream.get();
		//std::cout << label << std::endl;

	}


	ImageReader::~ImageReader()
	{
		delete[] currentImage;
	}


	void ImageReader::loadNext() {

		if (imageIndex >= numOfImages) {
			imageIndex = 0;
			imageStream.seekg(sizeof(imageFileHeader));
			labelStream.seekg(sizeof(labelFileHeader));
		}

		imageStream.read(currentImage, w*w);
		label = labelStream.get();
		//std::cout << label << std::endl;

		imageIndex++;

	}

	void ImageReader::drawCurrent() {
		for (int i = 0; i < w * w; i++) {
			char c = currentImage[i];
			pixel.setFillColor(sf::Color(c, c, c));

			for (int x = -int(scale / 2); x <= int(scale / 2); x++) {
				for (int y = -int(scale / 2); y <= int(scale / 2); y++) {
					pixel.setPosition(((i * scale) % (w * scale)) + x + int(scale / 2), (int(i / w) * scale) + y + int(scale / 2));
					data->window.draw(pixel);
				}
			}

		}
	}

}