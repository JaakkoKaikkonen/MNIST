#include "ImageReader.h"

namespace engine {

	ImageReader::ImageReader(gameDataRef data, const char* imageFilename, const char* labelFilename, const int numOfImages, const int imageWidth)
		: data(data),
		  numOfImages(numOfImages),
		  width(imageWidth)
	{
		pixel.setSize(sf::Vector2f(1, 1));

		currentImage = new char[width*width];

		//Open Image stream
		imageStream.open(imageFilename, std::ios::binary);

		if (!imageStream) {
			std::cout << "Error opening image file" << std::endl;
			return;
		}

		//Jump to the data
		imageStream.seekg(sizeof(imageFileHeader));



		//Open Label stream
		labelStream.open(labelFilename, std::ios::binary);

		if (!labelStream) {
			std::cout << "Error opening label file" << std::endl;
			return;
		}

		//Jump to the data
		labelStream.seekg(sizeof(labelFileHeader));


		//Read first image
		imageStream.read(currentImage, width*width);

		//Read first label
		label = labelStream.get();

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

		imageStream.read(currentImage, width*width);
		label = labelStream.get();

		imageIndex++;

	}

	void ImageReader::drawCurrent() {
		for (int i = 0; i < width * width; i++) {
			char c = currentImage[i];
			pixel.setFillColor(sf::Color(c, c, c));

			for (int x = -int(scale / 2); x <= int(scale / 2); x++) {
				for (int y = -int(scale / 2); y <= int(scale / 2); y++) {
					pixel.setPosition(((i * scale) % (width * scale)) + x + int(scale / 2), (int(i / width) * scale) + y + int(scale / 2));
					data->window.draw(pixel);
				}
			}

		}
	}

	Matrix<float> ImageReader::currentImageToInputMatrix() {
		Matrix<float> inputPixels(width * width, 1);
		for (int j = 0; j < width * width; j++) {
			inputPixels.set(j, float(unsigned char(currentImage[j])) / 255);
		}
		return inputPixels;
	}

}