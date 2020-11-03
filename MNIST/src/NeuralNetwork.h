#pragma once
#include "Matrix.h"
#include <fstream>
#include "ImGuiLog.h"
#include "ImageReader.h"

namespace engine {

	class NeuralNetwork
	{
	public:
		NeuralNetwork(int numOfInputs, int numOfhiddenNodes, int numOfoutputs);

		static float sigmoid(float num);

		static float sigmoidPrime(float num);

		int predict(const Matrix<float>& inputs);

		void updateMiniBatch(ImageReader& imageReader);

		void randomize();

	public:
		Matrix<float> weights1;
		Matrix<float> weights2;
		Matrix<float> bias_hidden;
		Matrix<float> bias_output;

	private:
		Matrix<float> inputs;
		Matrix<float> hiddenNodes;
		Matrix<float> outputs;

		int numOfInputs;
		int numOfhiddenNodes;
		int numOfOutputs;

		int miniBatchSize = 100;

		float learningRate = 0.01f;

	};

}

