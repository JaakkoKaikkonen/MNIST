#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


#include "imgui.h"
#include "imgui-SFML.h"

#include "ImageReader.h"
#include "NeuralNetwork.h"
#include "Drawing.h"


class GameState : public State
{
public:
	GameState(gameDataRef data);

	void init();

	void handleInput();
	void update(float dt);
	void draw();

	void predictDrawing();

private:
	gameDataRef data;

	sf::Color bgColor = sf::Color::Black;

	int trainingDataSize = 60000;
	int testDataSize = 10000;

	const char* modes[2] = {"Draw yourself", "Test Data"};
	int modeIndex = 0;

	Drawing drawing;

	const int imageWidth = 28;

	//Scale should be odd number
	const int imageScale = 7;

	ImageReader imageReader;

	ImageReader testImageReader;

	//ImGui///////////////////////////////////////
	ImGuiLog ImGuiLog;
	//////////////////////////////////////////////

	const int numOfHiddenNodes = 40;

	const int numOfMiniBatchesToTrainOn = 1000;

	NeuralNetwork nn;	
		

};


