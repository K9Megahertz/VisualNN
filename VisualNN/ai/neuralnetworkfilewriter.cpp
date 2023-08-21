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

#include "neuralnetworkfilewriter.h"

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



NeuralNetworkFileWriter::NeuralNetworkFileWriter()
{
	
}

NeuralNetworkFileWriter::~NeuralNetworkFileWriter()
{
	

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function readQuakeMapFile()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NeuralNetworkFileWriter::writeNeuralNetworkFile(NeuralNet& nn, std::string filename)
{
	std::ofstream file;

	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Writing out neuralnet file: " + filename);
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");


	//open the source file
	file.open(filename);

	//did the file open sucessfully?
	if (file.is_open()) {


		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "*******************************");
		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "* Writing Neural Network File *");
		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "*******************************");
		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");

		//do the save

		//loop through all of the layers
		for (unsigned int layerIndex = 0; layerIndex < nn.m_layers.size(); layerIndex++) {

			file << "{" << std::endl;  //start of layer definition

			//loop through all of the neurons in each layer
			for (unsigned int neuronIndex = 0; neuronIndex < nn.m_layers[layerIndex].m_neurons.size(); neuronIndex++) {

				file << "    {" << std::endl; //start of neuron definition

				//loop through all of the weights in each neuron if there are any
				if (nn.m_layers[layerIndex].m_neurons[neuronIndex].m_weights.size()) {

					//loop through all weights and the bias
					for (unsigned int weightIndex = 0; weightIndex < nn.m_layers[layerIndex].m_neurons[neuronIndex].m_weights.size(); weightIndex++) {

						//output weight values
						file << "        ";
						file << std::fixed << std::setprecision(14) << nn.m_layers[layerIndex].m_neurons[neuronIndex].m_weights[weightIndex] << std::endl;

					}
				}

				//end of neuron definition
				file << "    }" << std::endl;
			}

			//end of layer definition
			file << "}" << std::endl;
		}


		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Wrote out " + std::to_string(nn.m_layers.size()) + " Layers");
		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
		Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");


		//cleanup
		file.close();

		return true;
	}
	//TODO: file didnt open error out
	Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: Failed to open file");
	return false;

}






