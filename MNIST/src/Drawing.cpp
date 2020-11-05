#include "Drawing.h"

namespace engine {

	Drawing::Drawing(gameDataRef data) 
		: data(data)
	{

	}

	Drawing::~Drawing() {}


	void Drawing::update() {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			pixels.emplace_back(sf::RectangleShape(sf::Vector2f(penSize, penSize)));
			pixels[pixels.size() - 1].setPosition(sf::Vector2f(sf::Mouse::getPosition(data->window) - sf::Vector2i(penSize / 2, penSize / 2)));
		}

	}


	void Drawing::draw() {

		for (int i = 0; i < pixels.size(); i++) {
			data->window.draw(pixels[i]);
		}

	}

	void Drawing::clear() {
		pixels.clear();
	}


}