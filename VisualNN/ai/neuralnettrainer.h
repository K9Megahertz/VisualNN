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
#include <vector>
#include "neuralnet.h"
#include "../ai/mnist/mnistdataset.h"
#include "../util/rollingaverage.h"



class NeuralNetTrainer
{

public:
	NeuralNetTrainer();	
	~NeuralNetTrainer();
	
	void train(NeuralNet &nn, MNISTDataSet mds, unsigned int epochs);	
	void toggleTraining();
	void setLearningRate(double learningRate) { m_learningRate = learningRate; }


private:

	std::vector<double> feedForward(NeuralNet &nn, std::vector<double> input);
	void backPropagation(NeuralNet &nn, std::vector<double> outputs, std::vector<double> targets);	
	double sigmoid(double num);
	double sigmoidDerivative(double num);
	
	unsigned int m_curr_epoch;
	unsigned int m_curr_input;
	bool m_TrainingEnabled;
	double m_learningRate = 0.01;


};

