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

#include <algorithm>
#include <cmath>

#include <GLM/vec3.hpp> // glm::vec3
#include <GLM/vec4.hpp> // glm::vec4
#include <GLM/mat4x4.hpp> // glm::mat4
#include <GLM/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "system/BaseWindowsApp.h"
#include "util/logger.h"
#include "objects/quad.h"
#include "objects/sphere.h"
#include "objects/cube.h"
#include "objects/triangle.h"
#include "objects/triforce.h"
#include "objects/torus.h"
#include "renderer/renderer.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "ai/neuralnet.h"
#include "ai/mnist/mnistdataset.h"
#include "ai/mnist/mnistdatasetreader.h"
#include "ai/neuralnetworkfilereader.h"
#include "ai/neuralnettrainer.h"
#include "system/gthread.h"


class VisualNNApp : public BaseWindowsApp {

public:
	VisualNNApp(HINSTANCE hInstance, LPSTR ipCmdLine, int width, int height);
	~VisualNNApp();

	//implement the 3 main methods exposed from base class
	bool initialize();
	void update(float deltaTime);
	void cleanup();

	//extra stuffs
	void OnRightButtonDown(WPARAM wParam, LPARAM lParam);
	void OnRightButtonUp(WPARAM wParam, LPARAM lParam);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	void runNeuralNetwork();

private:

	void updateObjects();


	std::shared_ptr<Material> coloredMaterialSimple;
	std::unique_ptr<Thread<VisualNNApp>> m_thread;
	std::vector<std::shared_ptr<Texture>> m_Textures;

	NeuralNet nn;
	MNISTDataSet mnistdataset;
	NeuralNetTrainer nnt;

	bool m_paused;
	int m_threadspeed;

	bool wireframemode;
	bool m_drawconnections;

	POINT currmouse = { 0,0 };
	POINT lastmouse = { 0,0 };
	POINT savemouse = { 0,0 };


	//TODO: Move all this camera stuff to its own class


	//origin
	glm::vec3 camerapos = { 0, 0, 0 };
	float rotationangle = 0.0f;			// Y Rotation
	float lookupdown = -25.0;
	

	//side looking down
	//glm::vec3 camerapos = { 160, 160, -130 };
	//float rotationangle = 0.0f;			// Y Rotation
	//float lookupdown = -45.0;

	//center straight on in back
	//glm::vec3 camerapos = { 0, 0, -330 };
	//float rotationangle = 0.0f;			// Y Rotation
	//float lookupdown = 0.0;

	float cameraSpeed = 7.0f;

	glm::vec3 accel_vec = { 0,0,0 };
	glm::vec3 velocity = { 0,0,0 };	

	float radialangle = 0.0f;
	glm::vec3 radialpos = { 0, 0, 0 };




};
