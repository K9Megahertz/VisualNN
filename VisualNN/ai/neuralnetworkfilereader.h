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

#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../util/tokenizer.h"
#include "../util/logger.h"
#include "neuralnet.h"

class NeuralNet;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  NeuralNetworkFileReader - Reads a Neural Network text file in from disk.
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NeuralNetworkFileReader
{

public:
	
	bool readNeuralNetworkFile(NeuralNet& nn, std::string filename);
	NeuralNetworkFileReader();
	~NeuralNetworkFileReader();

private:

	Token* m_currenttoken;
	Tokenizer* m_tokenizer;
	
	int readLayer(Layer& layer);
	int readNeuron(Neuron& neuron);
	int readSignedInt(int& value);
	int readSignedFloat(float& value);
	int readSignedDouble(double& value);
	int readString(std::string& value);

	void eattoken(Token::TokenType tt);
	bool isCurrentTokenType(Token::TokenType tt);
		
};

