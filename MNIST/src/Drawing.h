#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Game.hpp"


class Drawing {

public:
	Drawing(gameDataRef data);
	~Drawing();

	void update();

	void draw();

	void clear();

private:
	gameDataRef data;

	std::vector<sf::RectangleShape> pixels;

	int penSize = 13;

	bool leftMouseButtonWasPressedLastUpdate = false;

	sf::Vector2f previousMousePos;

	int drawingAreaWidth = 196;
	int drawingAreaHeight = 196;

};



