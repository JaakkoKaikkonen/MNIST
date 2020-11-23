#include <string>
#include "GameState.hpp"
#include <iostream>



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


		ImGui::Combo("Mode", &modeIndex, modes, IM_ARRAYSIZE(modes));

		if (modes[modeIndex] == "Draw yourself") {
			if (ImGui::Button("Clear")) {
				drawing.clear();
			}
			if (ImGui::Button("Predict")) {
				this->predictDrawing();
			}
		}

		if (modes[modeIndex] == "Test Data") {
			if (ImGui::Button("Next")) {

				testImageReader.loadNext();

				ImGuiLog.AddLog(std::to_string(nn.predict(testImageReader.currentImageToInputMatrix())).c_str());
				ImGuiLog.AddLog("\n");
			}
		}


        ImGui::End(); // end window
		//////////////////////////////////////////////////////////////////////////////////////////////////

	}

	void GameState::draw() {

		data->window.clear(bgColor);


		drawing.draw();


		if (modes[modeIndex] == "Test Data") {
			testImageReader.drawCurrent(imageScale);
		}


		//ImGui///////////////////////////////////////////////////////////////////////////////////////////
		ImGuiLog.Draw("Logs");

		ImGui::SFML::Render(data->window);
		/////////////////////////////////////////////////////////////////////////////////////////////////

		data->window.display();
	
	}


	void GameState::predictDrawing() {

		texture.create(data->window.getSize().x, data->window.getSize().y);
		texture.update(data->window);

		sf::Image image = texture.copyToImage();

		sf::Image testImage;
		testImage.create(28, 28);

		Matrix<float> inputMatrix(imageWidth * imageWidth, 1);

		for (int y = 0; y < imageWidth; y++) {
			for (int x = 0; x < imageWidth; x++) {

				float value = 0;

				for (int i = -int(imageScale / 2); i <= int(imageScale / 2); i++) {
					for (int j = -int(imageScale / 2); j <= int(imageScale / 2); j++) {
						value += int(image.getPixel(int(imageScale / 2) + (x * imageScale) + i, int(imageScale / 2) + (y * imageScale) + j).r);
					}
				}

				inputMatrix.set(y * imageWidth + x, (value / ((imageScale * imageScale) * 255)));

				//std::cout << "-> " << (value / ((scale * scale) * 255)) << std::endl;

				/////////////////////////////////////////
				int c = value / ((imageScale * imageScale));


				sf::Color color(c, c, c);
				testImage.setPixel(x, y, color);
				testImage.saveToFile("testImage.png");
				////////////////////////////////////////
			}
		}

		ImGuiLog.AddLog(std::to_string(nn.predict(inputMatrix)).c_str());
		ImGuiLog.AddLog("\n");
	}


}


