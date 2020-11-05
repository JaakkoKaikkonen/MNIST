#include "Drawing.h"

namespace engine {

	Drawing::Drawing(gameDataRef data) 
		: data(data)
	{

	}

	Drawing::~Drawing() {}


	void Drawing::update() {

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			leftMouseButtonWasPressedLastUpdate = false;

		} else {

			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(data->window));

			if (leftMouseButtonWasPressedLastUpdate) {

				sf::Vector2f mouseMoveVector = mousePos - previousMousePos;
				float mouseMoveVectorLength = sqrt((mouseMoveVector.x * mouseMoveVector.x) + (mouseMoveVector.y * mouseMoveVector.y));

				for (int i = 0; i < int(mouseMoveVectorLength); i++) {
					pixels.emplace_back(sf::RectangleShape(sf::Vector2f(penSize, penSize)));
					pixels[pixels.size() - 1].setPosition(previousMousePos + ((i / mouseMoveVectorLength) * mouseMoveVector));
				}

			}

			pixels.emplace_back(sf::RectangleShape(sf::Vector2f(penSize, penSize)));
			pixels[pixels.size() - 1].setPosition(mousePos);

			previousMousePos = mousePos;
			leftMouseButtonWasPressedLastUpdate = true;
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