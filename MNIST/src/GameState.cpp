#include <string>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include "Utility.hpp"



namespace engine {

	GameState::GameState(gameDataRef data)
		: data(data),
		  imageReader(data, "train-images.idx3-ubyte", "train-labels.idx1-ubyte", 60000),
		  nn(28*28, 15, 10)
	{
		this->init();

		for (int i = 0; i < 100000; i++) {
			//Train
			nn.updateMiniBatch(imageReader);

			//Try
			Matrix<float> inputPixels(28 * 28, 1);
			for (int j = 0; j < 28 * 28; j++) {
				//std::cout << float(unsigned char(imageReader.currentImage[j])) / 255 << std::endl;
				inputPixels.set(j, float(unsigned char(imageReader.currentImage[j])) / 255);
			}
			std::cout << "Predict: " << nn.predict(inputPixels) << "\t Correct: " << imageReader.label << std::endl;
		}
	}

	void GameState::init() {
		//std::cout << "Game state" << std::endl;

		//ImGui///////////////////////////////////////////////////////////////////////////////////
		ImGui::SFML::Init(data->window);
		//////////////////////////////////////////////////////////////////////////////////////////
	}

	void GameState::handleInput() {
		sf::Event event;
		while (data->window.pollEvent(event)) {
			//ImGui///////////////////////////////////////////////////////////////////////////////////
			 ImGui::SFML::ProcessEvent(event);
			//////////////////////////////////////////////////////////////////////////////////////////

			if (sf::Event::Closed == event.type) {
				data->window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				imageReader.loadNext();
			}

		}

	}

	void GameState::update(float dt) {

		//ImGui///////////////////////////////////////////////////////////////////////////////////////////
		ImGui::SFML::Update(data->window, sf::seconds(dt));

		ImGui::Begin("Sample window"); // begin window



        ImGui::End(); // end window
		//////////////////////////////////////////////////////////////////////////////////////////////////


	}

	void GameState::draw() {

		data->window.clear(bgColor);

		//ImGui///////////////////////////////////////////////////////////////////////////////////////////
		ImGui::SFML::Render(data->window);
		/////////////////////////////////////////////////////////////////////////////////////////////////

		
		imageReader.drawCurrent();

		data->window.display();
	
	}


}


