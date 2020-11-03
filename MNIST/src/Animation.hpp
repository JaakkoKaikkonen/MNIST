#pragma once

#include <SFML/Graphics.hpp>

namespace engine {

	class Animation
	{
	public:
		Animation(sf::Sprite& sprite, sf::IntRect* animationFrames, unsigned int size, float animationTime);

		void animate();

		void animation();

		void reset();

	private:
		sf::Clock clock;

		sf::Sprite& sprite;

		sf::IntRect* animationFrames;

		unsigned int size;

		float animationTime;

		unsigned int animationiterator = 0;

		bool start = true;
	};

}