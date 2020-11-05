#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace engine {

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

		int penSize = 5;


	};



}