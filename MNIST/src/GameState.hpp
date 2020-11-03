#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Animation.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "ImageReader.h"
#include "NeuralNetwork.h"

namespace engine {

	class GameState : public State
	{
	public:
		GameState(gameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw();

	private:
		gameDataRef data;

		sf::Color bgColor = sf::Color::White;

		ImageReader imageReader;

		ImageReader testImageReader;

		//ImGui///////////////////////////////////////
		


		//////////////////////////////////////////////

		NeuralNetwork nn;
	};

}

