#include "Drawing.h"


Drawing::Drawing(gameDataRef data) 
	: data(data)
{

}

Drawing::~Drawing() {}


void Drawing::update() {

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(data->window));

	if (mousePos.x <= drawingAreaWidth && mousePos.y <= drawingAreaHeight) {

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			leftMouseButtonWasPressedLastUpdate = false;

		} else {

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

}


void Drawing::draw() {

	//Draw pixels
	for (int i = 0; i < pixels.size(); i++) {
		data->window.draw(pixels[i]);
	}

	//Draw black bars to hide pixels that go over the drawing area
	sf::RectangleShape blackBar1(sf::Vector2f(penSize, drawingAreaHeight + penSize));
	blackBar1.setPosition(drawingAreaWidth, 0);
	blackBar1.setFillColor(sf::Color::Black);

	sf::RectangleShape blackBar2(sf::Vector2f(drawingAreaWidth + penSize, penSize));
	blackBar2.setPosition(0, drawingAreaHeight);
	blackBar2.setFillColor(sf::Color::Black);

	data->window.draw(blackBar1);
	data->window.draw(blackBar2);

}

void Drawing::clear() {
	pixels.clear();
}