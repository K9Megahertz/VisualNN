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

#include "neuralnet.h"

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


NeuralNet::NeuralNet() {

	m_curr_epoch = 0;
	m_curr_input = 0;
	
}

NeuralNet::NeuralNet(const std::vector<int> topology) {

	m_curr_epoch = 0;
	m_curr_input = 0;


	//loop through all of the layer definitions in the topology
	for (unsigned int i = 0; i < topology.size(); i++) {

		//alias for convenience
		int neuroncountforlayer = topology[i];

		Layer newlayer;

		//loop though the count of neurons we need to create
		for (int neuronindex = 0; neuronindex < neuroncountforlayer; neuronindex++) {

			//if this is not the first layer (input) then we are going to have the weights populated with the count of neurons in the previous layer plus a bias weight
			Neuron newneuron(i ? topology[i - 1] + 1 : 0);

			//add the neuron to the layer
			newlayer.addNeuron(newneuron);

		}

		//now that we have populated layer of neurons
		//add the layer to the list of layers in the Neural Network	
		m_layers.push_back(newlayer);
	}
}

NeuralNet::~NeuralNet() {}




