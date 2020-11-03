#include <string>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include "Utility.hpp"



namespace engine {

	GameState::GameState(gameDataRef data)
		: data(data),
		  imageReader(data, "train-images.idx3-ubyte", "train-labels.idx1-ubyte", 60000),
		  testImageReader(data, "t10k-images.idx3-ubyte", "t10k-labels.idx1-ubyte", 10000),
		  nn(28*28, 30, 10)
	{
		this->init();

		//Train
		for (int i = 0; i < 100000; i++) {
			
			nn.updateMiniBatch(imageReader);

			if (i % 1000 == 0) {
				std::cout << "MiniBatch iteration: " << i << std::endl;
			}

		}

		//Test
		int correctClassifications = 0;
		for (int i = 0; i < 10000; i++) {
			Matrix<float> inputPixels(28 * 28, 1);
			for (int j = 0; j < 28 * 28; j++) {
				inputPixels.set(j, float(unsigned char(testImageReader.currentImage[j])) / 255);
			}
			if (nn.predict(inputPixels) == testImageReader.label) {
				correctClassifications++;
			}
			testImageReader.loadNext();
		}

		std::cout << "Correct classifications: " << correctClassifications << std::endl;


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


