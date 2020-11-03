#include "NeuralNetwork.h"
#include <math.h>
#include <string>

namespace engine {

	NeuralNetwork::NeuralNetwork(int _numOfInputs, int _numOfhiddenNodes, int _numOfOutputs)
		: inputs(_numOfInputs, 1),
		hiddenNodes(_numOfhiddenNodes, 1),
		outputs(_numOfOutputs, 1),
		weights1(_numOfhiddenNodes, _numOfInputs),
		weights2(_numOfOutputs, _numOfhiddenNodes),
		bias_hidden(_numOfhiddenNodes, 1),
		bias_output(_numOfOutputs, 1),
		numOfInputs(_numOfInputs),
		numOfhiddenNodes(_numOfhiddenNodes),
		numOfOutputs(_numOfOutputs)
	{
		weights1.randomize();
		weights2.randomize();
		bias_hidden.randomize();
		bias_output.randomize();
	}


	float NeuralNetwork::sigmoid(float num) {
		return (1 / (1 + exp(-num)));
	}

	float NeuralNetwork::sigmoidPrime(float num) {
		return (sigmoid(num) * (1 - sigmoid(num)));
	}


	int NeuralNetwork::predict(const Matrix<float>& inputs) {

		hiddenNodes = weights1 * inputs;
		hiddenNodes += bias_hidden;
		hiddenNodes.map(NeuralNetwork::sigmoid);

		outputs = weights2 * hiddenNodes;
		outputs += bias_output;
		outputs.map(NeuralNetwork::sigmoid);
		
		int index = 1;
		float record = 0;
		for (int i = 1; i <= outputs.rows; i++) {
			if (outputs.get(i, 1) > record) {
				record = outputs.get(i, 1);
				index = i;
			}
		}

		return index - 1;
	}


	void NeuralNetwork::updateMiniBatch(ImageReader& imageReader) {
		Matrix<float> weightGradient1(numOfhiddenNodes, numOfInputs);
		weightGradient1.zeros();
		Matrix<float> weightGradient2(numOfOutputs, numOfhiddenNodes);
		weightGradient2.zeros();
		Matrix<float> biasGradient1(numOfhiddenNodes, 1);
		biasGradient1.zeros();
		Matrix<float> biasGradient2(numOfOutputs, 1);
		biasGradient2.zeros();


		//For every input in miniBatch
		for (int i = 0; i < miniBatchSize; i++) {
			
			//Get input Pixels from imageReader
			Matrix<float> inputPixels(numOfInputs, 1);
			for (int j = 0; j < numOfInputs; j++) {
				inputPixels.set(j, float(unsigned char(imageReader.currentImage[j])) / 255);
			}

			//Create correct ouput vector
			Matrix<float> correctOutput(numOfOutputs, 1);
			correctOutput.zeros();
			correctOutput.set(imageReader.label, 1);


			//Feed forward
			hiddenNodes = weights1 * inputPixels;
			hiddenNodes += bias_hidden;
			Matrix<float> z1(numOfhiddenNodes, 1);
			z1 = hiddenNodes;
			hiddenNodes.map(NeuralNetwork::sigmoid);
			Matrix<float> a1(numOfhiddenNodes, 1);
			a1 = hiddenNodes;

			outputs = weights2 * hiddenNodes;
			outputs += bias_output;
			Matrix<float> z2(numOfOutputs, 1);
			z2 = outputs;
			outputs.map(NeuralNetwork::sigmoid);
			Matrix<float> a2(numOfOutputs, 1);
			a2 = outputs;

			//Calculate errors
			Matrix<float> outputError(numOfOutputs, 1);
			z2.map(NeuralNetwork::sigmoidPrime);
			outputError = Matrix<float>::hadamardProduct((a2 - correctOutput), z2);

			Matrix<float> hiddenError(numOfhiddenNodes, 1);
			z1.map(NeuralNetwork::sigmoidPrime);
			hiddenError = Matrix<float>::hadamardProduct(Matrix<float>::multiply(Matrix<float>::transpose(weights2), outputError), z1);

			//Add gradients
			weightGradient1 += Matrix<float>::multiply(hiddenError, Matrix<float>::transpose(inputPixels));
			weightGradient2 += Matrix<float>::multiply(outputError, Matrix<float>::transpose(a1));

			biasGradient1 += hiddenError;
			biasGradient2 += outputError;


			imageReader.loadNext();
		}


		weights1 -= Matrix<float>::multiply((learningRate / miniBatchSize), weightGradient1);
		weights2 -= Matrix<float>::multiply((learningRate / miniBatchSize), weightGradient2);

		bias_hidden -= Matrix<float>::multiply((learningRate / miniBatchSize), biasGradient1);
		bias_output -= Matrix<float>::multiply((learningRate / miniBatchSize), biasGradient2);


	}



	void NeuralNetwork::randomize() {
		weights1.randomize();
		weights2.randomize();
		bias_hidden.randomize();
		bias_output.randomize();
	}


}
