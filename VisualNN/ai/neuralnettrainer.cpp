//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// MIT License
// 
// Copyright(c) 2023 Gerald Filimonov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "NeuralNetTrainer.h"
#include "windows.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  CTORs/DTORs
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



NeuralNetTrainer::NeuralNetTrainer() {

	m_curr_epoch = 0;
	m_curr_input = 0;
	m_TrainingEnabled = true;

}

NeuralNetTrainer::~NeuralNetTrainer() {}
	
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function sigmoid()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double NeuralNetTrainer::sigmoid(double num) {

	return 1.0 / (1.0 + exp(-num));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function derivativeSigmoid()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double NeuralNetTrainer::sigmoidDerivative(double num) {
	return sigmoid(num) * (1 - sigmoid(num));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function train()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetTrainer::train(NeuralNet &nn, MNISTDataSet mds , unsigned int epochs) {
	
	//ignore epoch count and just run one iteration since this is interactive app
	int num_images = mds.images.size();
	double error = 0.0;			
	std::vector<double> outputs = feedForward(nn, mds.images[m_curr_input%num_images].pixels);
	std::vector<double> targetvals;  // targets as an array of 10 doubles 0.0-1.0

	targetvals.resize(10);
	for (int j = 0; j < 10; j++) {
		targetvals[j] = (j == mds.images[m_curr_input%num_images].label ? 1.0 : 0.0);				
		error += (targetvals[j] - outputs[j]) * (targetvals[j] - outputs[j]);
	}
	if (m_TrainingEnabled)
		backPropagation(nn, outputs, targetvals);			

	m_curr_input++;


}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function feedForward()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<double> NeuralNetTrainer::feedForward(NeuralNet& nn, std::vector<double> input) {

	for (unsigned int i = 0; i < nn.m_layers[0].m_neurons.size(); i++) {
		nn.m_layers[0].m_neurons[i].value = input[i];
	}

	//loop through all of the layers except the first one since it just contains input neurons
	for (unsigned int i = 1; i < nn.m_layers.size(); i++) {

		//loop through all of the neurons in the layer
		for (unsigned int n = 0; n < nn.m_layers[i].m_neurons.size(); n++) {

			double sum = 0.0;
			size_t previousLayerNeuronCount = nn.m_layers[i - 1].m_neurons.size();

			//for each neuron calcluate x0*w0+x1*w1+x2.......+b
			for (unsigned int w = 0; w < previousLayerNeuronCount; w++) {

				double xi = nn.m_layers[i - 1].m_neurons[w].value;
				double wi = nn.m_layers[i].m_neurons[n].m_weights[w];

				sum += xi * wi;
			}

			//add bias term
			sum += nn.m_layers[i].m_neurons[n].m_weights[previousLayerNeuronCount];

			//using tanh as a sigmoid function
			sum = sigmoid(sum);

			nn.m_layers[i].m_neurons[n].value = sum;

		}
	}

	//values to return
	std::vector<double> ret;

	for (unsigned int i = 0; i < nn.m_layers[nn.m_layers.size() - 1].m_neurons.size(); i++) {
		ret.push_back(nn.m_layers[nn.m_layers.size() - 1].m_neurons[i].value);
	}

	return ret;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function backPropagation()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetTrainer::backPropagation(NeuralNet &nn, std::vector<double> outputs, std::vector<double> targets) {
	

	//gather up the output errors and save as currentErrors
	std::vector<double> currentLayerErrors;
	for (unsigned int n = 0; n < nn.m_layers[nn.m_layers.size() - 1].m_neurons.size(); n++) {   //loop through the size of the last layer.	
		double currentError = (targets[n] - outputs[n]) * sigmoidDerivative(outputs[n]);
		currentLayerErrors.push_back(currentError);
	}

	//loop backwards through the layers
	for (size_t layerIndex = nn.m_layers.size() - 1; layerIndex > 0; layerIndex--) {
		
		size_t currentLayerNeuronCount = nn.m_layers[layerIndex].m_neurons.size();
		size_t previousLayerIndex = layerIndex - 1;
		size_t previousLayerNeuronCount = nn.m_layers[previousLayerIndex].m_neurons.size();

		//update weights based on the errors we have
		//Sleep(10);
		//go through the neurons in each layer, output layer would be first
		for (unsigned int neuronIndex = 0; neuronIndex < currentLayerNeuronCount; neuronIndex++) {
			
			//loop through a count of the neurons in the previous layer, cause thats how many weights well have.
			for (unsigned int weightIndex = 0; weightIndex < previousLayerNeuronCount; weightIndex++) {

				nn.m_layers[layerIndex].m_neurons[neuronIndex].m_weights[weightIndex] += m_learningRate * currentLayerErrors[neuronIndex] * nn.m_layers[previousLayerIndex].m_neurons[weightIndex].value;

			}

			//update bias
			nn.m_layers[layerIndex].m_neurons[neuronIndex].m_weights[previousLayerNeuronCount] += m_learningRate * currentLayerErrors[neuronIndex];
		}

		//calculate the hidden errors
		std::vector<double> previousLayerErrors;

		//loop through all of the previouslayer neurons and process each one
		for (unsigned int previousLayerNeuronIndex = 0; previousLayerNeuronIndex < previousLayerNeuronCount; previousLayerNeuronIndex++) {

			double sum = 0.0;

			//loop through all of the current layer neurons
			for (unsigned int currentLayerNeuronIndex = 0; currentLayerNeuronIndex < currentLayerNeuronCount; currentLayerNeuronIndex++) {
				sum += nn.m_layers[layerIndex].m_neurons[currentLayerNeuronIndex].m_weights[previousLayerNeuronIndex] * currentLayerErrors[currentLayerNeuronIndex];
			}

			previousLayerErrors.push_back(sum * sigmoidDerivative(nn.m_layers[layerIndex - 1].m_neurons[previousLayerNeuronIndex].value));
		}

		//make previousErrors become the currenterrors and loop
		currentLayerErrors = previousLayerErrors;

	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function backPropagation()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetTrainer::toggleTraining() {
	m_TrainingEnabled = !m_TrainingEnabled;
}

