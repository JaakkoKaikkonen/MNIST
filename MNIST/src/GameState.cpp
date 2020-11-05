#include <string>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include "Utility.hpp"



namespace engine {

	GameState::GameState(gameDataRef data)
		: data(data),
		  drawing(data),
		  imageReader(data, "train-images.idx3-ubyte", "train-labels.idx1-ubyte", 60000, imageWidth),
		  testImageReader(data, "t10k-images.idx3-ubyte", "t10k-labels.idx1-ubyte", 10000, imageWidth),
		  nn(imageWidth * imageWidth, numOfHiddenNodes, 10)
	{
		this->init();
	}

	void GameState::init() {

		//ImGui///////////////////////////////////////////////////////////////////////////////////
		ImGui::SFML::Init(data->window);
		//////////////////////////////////////////////////////////////////////////////////////////

		//Train
		for (int i = 0; i < numOfMiniBatchesToTrainOn; i++) {

			nn.updateMiniBatch(imageReader);

			if (i % 1000 == 0) {
				std::cout << "MiniBatch iteration: " << i << std::endl;
			}

		}

		//Test
		int correctClassifications = 0;
		for (int i = 0; i < 10000; i++) {
			if (nn.predict(testImageReader.currentImageToInputMatrix()) == testImageReader.label) {
				correctClassifications++;
			}
			testImageReader.loadNext();
		}

		std::cout << "Correct classifications: " << correctClassifications << std::endl;


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
				testImageReader.loadNext();

				ImGuiLog.AddLog(std::to_string(nn.predict(testImageReader.currentImageToInputMatrix())).c_str());
				ImGuiLog.AddLog("\n");
			}

		}

	}

	void GameState::update(float dt) {

		drawing.update();

		//ImGui///////////////////////////////////////////////////////////////////////////////////////////
		ImGui::SFML::Update(data->window, sf::seconds(dt));


		ImGui::Begin("UI"); // begin window

		if (ImGui::Button("Clear")) {
			drawing.clear();
		}

        ImGui::End(); // end window
		//////////////////////////////////////////////////////////////////////////////////////////////////

	}

	void GameState::draw() {

		data->window.clear(bgColor);


		drawing.draw();

		testImageReader.drawCurrent();


		//ImGui///////////////////////////////////////////////////////////////////////////////////////////
		ImGuiLog.Draw("Logs");

		ImGui::SFML::Render(data->window);
		/////////////////////////////////////////////////////////////////////////////////////////////////

		data->window.display();
	
	}


}


