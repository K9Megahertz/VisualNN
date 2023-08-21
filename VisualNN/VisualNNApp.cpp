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
// 
// 
// Author: Gerald Filimonov
// Email: k9megahertz@yahoo.com
// GitHub: k9megahertz
// Date: 08/20/2023
// 
// Description: Visualization Tool for perceptron based neural networks
//
// Update History:
//  - 08/20/2023: [Initial Version]
//  
//  
//
// Revision History:
//  - Version [Version Number]: [Date of Version]
//    [Brief description of the changes made in this version]
//    [Additional details if necessary]
//
//
////////////////////////////////////////////////////////////////////////


#include "VisualNNApp.h"

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


VisualNNApp::VisualNNApp(HINSTANCE hInstance, LPSTR ipCmdLine, int width, int height) : BaseWindowsApp(hInstance, ipCmdLine, width, height) {

}

VisualNNApp::~VisualNNApp() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Initialize()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VisualNNApp::initialize() {

	//I love to singa!	
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Initializing");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Done!");


	//setup some flags
	wireframemode = false;
	m_drawconnections = true;

	nnt.setLearningRate(0.01);

	//setup AI thread to run the Neural Network, call start later
	m_thread = std::make_unique<Thread<VisualNNApp>>(this, &VisualNNApp::runNeuralNetwork);
	m_threadspeed = 1000;  //set default speed

	//Initialize the pretties
	Renderer::init();

	//Load AI stuff
	MNISTDataSetReader dsr;
	dsr.loadMNISTData(mnistdataset, "./mnistdata/train-images.idx3-ubyte", "./mnistdata/train-labels.idx1-ubyte");

	NeuralNetworkFileReader nnfr;
	nnfr.readNeuralNetworkFile(nn, "./nnexamples/mnistbase_784_576_256_10 output at 20 epochs.txt");	

	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/0-whiteonblack.png"));	
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/1-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/2-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/3-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/4-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/5-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/6-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/7-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/8-whiteonblack.png"));
	m_Textures.push_back(TextureManager::getInstance().getTexture("textures/9-whiteonblack.png"));


	//initmouse tracking variables
	GetCursorPos(&currmouse);
	lastmouse = currmouse;

	//loop through each layer and create all the objects
	for (int l = 0; l < nn.m_layers.size() - 1; l++) {

		int length = glm::sqrt(nn.m_layers[l].m_neurons.size());

		//loop through each row and column of the layer and create all the objects
		for (int row = 0; row < length; row++) {
			for (int col = 0; col < length; col++) {

				Sphere s(0.0, 0.0, 0.0, 3);						
				
				std::shared_ptr<Material> mat = MaterialGenerator::GenerateMaterial("coloredMaterialInstancedtest");

				//set the color to a greyscale intensity value 0.0f -> 1.0f
				float color = (float)nn.m_layers[l].m_neurons[row * length + col].value;

				mat->m_AmbientColor = { glm::vec4(color, color, color, 1.0) };
				mat->m_DiffuseColor = { glm::vec4(color, color, color, 1.0) };
				mat->m_SpecularColor = { glm::vec4(color, color, color, 1.0) };
				mat->setTexture(m_Textures[0]);  //texture

				s.setMaterial(mat);
				s.setScale(glm::vec3(2.0, 2.0, 2.0));				
				
				float jitter = (rand() / static_cast<float>(RAND_MAX) * 18) - 9;
				//float jitter = 0;

				glm::vec3 loc = glm::vec3(-((col * 4) - (length * 4 / 2)), (row * 4) - (length * 4 / 2), l * 90 + (l == nn.m_layers.size() - 1 || l == 0 ? 0 : jitter));

				glm::vec3 newloc = -loc;

				s.setPosition(newloc);
				
				nn.m_layers[l].m_neurons[row * length + col].m_Object = std::make_shared<Sphere>(s);

			}
		}
	}

	//create output layer neurons/objects

	for (int i = 0; i < 10; i++) {

		Cube c(0.0, 0.0, 0.0);

		std::shared_ptr<Material> mat = MaterialGenerator::GenerateMaterial("coloredMaterialInstancedtest");
		c.setScale(glm::vec3(10.0, 10.0, 10.0));		

		int lastLayerIndex = nn.m_layers.size() - 1;
		float color = nn.m_layers[lastLayerIndex].m_neurons[i].value;

		mat->m_AmbientColor = glm::vec4(color, color, color, 1.0);
		mat->m_DiffuseColor = glm::vec4(color, color, color, 1.0);
		mat->m_SpecularColor = glm::vec4(color, color, color, 1.0);
		mat->setTexture(m_Textures[0]);  
		c.setMaterial(mat);

		int neuroncount = nn.m_layers[lastLayerIndex].m_neurons.size();

		glm::vec3 loc = glm::vec3((((float)i + 0.5) * 12) - (neuroncount * 12 / 2), 0, lastLayerIndex * -90);

		c.setPosition(loc);
		nn.m_layers[lastLayerIndex].m_neurons[i].m_Object = std::make_shared<Cube>(c);

	}

	coloredMaterialSimple = MaterialGenerator::GenerateMaterial("coloredMaterialSimple");
	coloredMaterialSimple->setTexture(m_Textures[0]);

	//TODO: make this actually work
	Renderer::setWireFrame(false);

	//Start the AI thread
	m_thread->start();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function update() 
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisualNNApp::update(float deltaTime) {


	radialangle += 0.1;

	//rotationangle = radialangle;
	//float dist = 250.0f;
	//camerapos = glm::vec3(std::sin(glm::radians(radialangle)) * dist, 160.0, std::cos(glm::radians(radialangle)) * dist - 120.0f);
	



	////////////////////////////////////////////////////////
	//Create the 3 main matrices. Model, View and Projection
	////////////////////////////////////////////////////////

	//////////////////////////////
	//create Model matrix (dont really need this here since well be using the matrix stored with each object
	//////////////////////////////

	glm::mat4 matrixModel = glm::mat4(1.0f);

	//////////////////////////////
	//create View matrix
	//////////////////////////////

	//move the camera to where it should be
	glm::mat4 matrixTranslation = glm::translate(glm::mat4(1.0f), -camerapos);	
	

	glm::mat4 matrixRotation = glm::mat4(1.0f);
	matrixRotation = glm::rotate(matrixRotation, glm::radians(-lookupdown), glm::vec3(1.0f, 0.0f, 0.0f));
	matrixRotation = glm::rotate(matrixRotation, glm::radians(-rotationangle), glm::vec3(0.0f, 1.0f, 0.0f));

	//Multiply them together (concatenate into one matrix)
	glm::mat4 matrixView = matrixRotation * matrixTranslation;



	//////////////////////////////
	//create Projection matrix	    
	//////////////////////////////
	glm::mat4 matrixProjection = glm::perspective(45.0f, (float)m_ClientWidth / (float)m_ClientHeight, 0.01f, 10000.0f);


	//////////////////////////////
	//update the scene
	//////////////////////////////
	updateObjects();


	////////////////////////
	// Render
	////////////////////////

	std::srand(0); //so we draw the same random lines each time

	if (wireframemode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	Renderer::clear({ 0.0, 0.5, 0.5 });	
	
	Renderer::begin(matrixView, matrixProjection);
	


	////////////////////////////
	// Draw the first n-1 layers
	////////////////////////////

	int lastlayerIndex = nn.m_layers.size() - 1;
	
	//loop through each layer and create all the objects
	for (int l = 0; l < lastlayerIndex; l++) {
		//for (int l = 0; l < 1; l++) {

		int length = glm::sqrt(nn.m_layers[l].m_neurons.size());

		//loop through each row and column of the layer and create all the objects
		for (int row = 0; row < length; row++) {
			for (int col = 0; col < length; col++) {
				std::shared_ptr<Object> obj = nn.m_layers[l].m_neurons[row * length + col].m_Object;
				Renderer::submitMeshInstanced(obj->getMesh(), obj->getMaterial(), obj->getModelMatrix());

				//do the dew?
				if (m_drawconnections) {
					//do the lines
					for (int dst = 0; dst < nn.m_layers[l + 1].m_neurons.size(); dst++) {   //loop through all the neurons in the next layer

						//limit the amount of lines we draw because its an insane amount
						float chancetodrawline = 0.0f;

						if (l == nn.m_layers.size() - 2)
							chancetodrawline = 0.10;  //draw quite a bit more on the output layer
						else
							chancetodrawline = 0.002; //otherwise not a whole lot

						if (rand() / static_cast<float>(RAND_MAX) < chancetodrawline) {
							std::shared_ptr<Object> dobj = nn.m_layers[l + 1].m_neurons[dst].m_Object;

							//start vertex
							Vertex v0;
							v0.m_Position = obj->getPosition();
							v0.m_Color = obj->getMaterial()->m_DiffuseColor;

							//end vertex
							Vertex v1;
							v1.m_Position = dobj->getPosition();
							v1.m_Color = dobj->getMaterial()->m_DiffuseColor;

							Renderer::SubmitLine(v0, v1, coloredMaterialSimple);
						}
					}
				}
			}
		}
	}
	

	////////////////////////
	// Render last layer
	////////////////////////

	for (int i = 0; i < nn.m_layers[lastlayerIndex].m_neurons.size(); i++) {
		std::shared_ptr<Object> obj = nn.m_layers[lastlayerIndex].m_neurons[i].m_Object;
		Renderer::submitMeshInstanced(obj->getMesh(), obj->getMaterial(), obj->getModelMatrix());

	}
	
	
	////////////////////////
	// Render Numbers
	// TODO: make these static objects rather than recreating every frame
	////////////////////////


	for (int i = 0; i < nn.m_layers[lastlayerIndex].m_neurons.size(); i++) {
		Quad q(0.0, 0.0, 0.0, 1.0);
		q.setScale(glm::vec3(10.0, 10.0, 0.0));

		float color = nn.m_layers[lastlayerIndex].m_neurons[i].value;

		std::shared_ptr<Material> mat = MaterialGenerator::GenerateMaterial("texturedMaterialSimple");
		mat->m_AmbientColor = glm::vec4(color, color, color, 1.0);
		mat->m_DiffuseColor = glm::vec4(color, color, color, 1.0);
		mat->m_SpecularColor = glm::vec4(color, color, color, 1.0);
		mat->setTexture(m_Textures[i]);  //incremental texture
		q.setMaterial(mat);

		int neuroncount = nn.m_layers[lastlayerIndex].m_neurons.size();

		glm::vec3 loc = glm::vec3((((float)i + 0.5) * 12) - (neuroncount * 12 / 2), 10, lastlayerIndex * -90 - 5);
		q.setPosition(loc);


		Renderer::submitMesh(q.getMesh(), q.getMaterial(), q.getModelMatrix());


	}

	Renderer::end();

	// Swap front and back buffers	
	swapBuffers();



	////////////////////////////////////////////
	//                                        //
	//  Handle Keyboard and Mouse Input       // 
	//                                        //	
	////////////////////////////////////////////

	//update mouse position
	GetCursorPos(&currmouse);

	//right click enables mouse panning mode
	if (isRightMousePressed()) {
		if (currmouse.x != lastmouse.x || currmouse.y != lastmouse.y) { //did we actually move?

			rotationangle -= (currmouse.x - lastmouse.x) / 3.0f;
			lookupdown -= (currmouse.y - lastmouse.y) / 3.0f;

			if (lookupdown > 89.0f) {
				lookupdown = 89.0f;
			}

			if (lookupdown < -89.0f) {
				lookupdown = -89.0f;
			}

			SetCursorPos(m_ClientWidth / 2, m_ClientHeight / 2);
			GetCursorPos(&currmouse);
			lastmouse = currmouse;
		}
	}


	//push camera forward
	if (isKeyPressed('W')) {

		accel_vec.x = -((float)sin(glm::radians(rotationangle)) * (float)cos(glm::radians(lookupdown)));
		accel_vec.y = ((float)sin(glm::radians(lookupdown)));
		accel_vec.z = -((float)cos(glm::radians(rotationangle)) * (float)cos(glm::radians(lookupdown)));

		accel_vec.x *= cameraSpeed * deltaTime;
		accel_vec.y *= cameraSpeed * deltaTime;
		accel_vec.z *= cameraSpeed * deltaTime;

		velocity.x += accel_vec.x;
		velocity.y += accel_vec.y;
		velocity.z += accel_vec.z;
	}



	//pull camera back
	if (isKeyPressed('S')) {
		accel_vec.x = ((float)sin(glm::radians(rotationangle)) * (float)cos(glm::radians(lookupdown)));
		accel_vec.y = -((float)sin(glm::radians(lookupdown)));
		accel_vec.z = ((float)cos(glm::radians(rotationangle)) * (float)cos(glm::radians(lookupdown)));

		accel_vec.x *= cameraSpeed * deltaTime;
		accel_vec.y *= cameraSpeed * deltaTime;
		accel_vec.z *= cameraSpeed * deltaTime;

		velocity.x += accel_vec.x;
		velocity.y += accel_vec.y;
		velocity.z += accel_vec.z;

	}

	//strafe camera left
	if (isKeyPressed('A')) {
		accel_vec.x = -(float)sin(glm::radians(rotationangle + 90));
		accel_vec.z = -(float)cos(glm::radians(rotationangle + 90));

		accel_vec.x *= cameraSpeed * deltaTime;
		accel_vec.z *= cameraSpeed * deltaTime;

		velocity.x += accel_vec.x;
		velocity.z += accel_vec.z;

	}

	//strafe camera right
	if (isKeyPressed('D')) {

		accel_vec.x = -(float)sin(glm::radians(rotationangle - 90));
		accel_vec.z = -(float)cos(glm::radians(rotationangle - 90));		

		accel_vec.x *= cameraSpeed * deltaTime;
		accel_vec.z *= cameraSpeed * deltaTime;

		velocity.x += accel_vec.x;
		velocity.z += accel_vec.z;

	}

	// Raise the camera up
	if (isKeyPressed(VK_SPACE)) {
		accel_vec.y = 1.0;
		accel_vec.y *= cameraSpeed * deltaTime;
		velocity.y += accel_vec.y;

	}

	// Lower the camera down 
	if (isKeyPressed('Z')) {
		accel_vec.y = -1.0;
		accel_vec.y *= cameraSpeed * deltaTime;
		velocity.y += accel_vec.y;
	}


	//apply friction
	velocity.x = velocity.x * 0.9f;
	velocity.y = velocity.y * 0.9f;
	velocity.z = velocity.z * 0.9f;

	//Update Camera
	camerapos.x += velocity.x;
	camerapos.y += velocity.y;
	camerapos.z += velocity.z;



}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function runNeuralNetwork() 
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisualNNApp::runNeuralNetwork() {
	//update the neuralnetwork
	nnt.train(nn, mnistdataset, 1);         //train(neuralnet object, dataset to use, # epochs)

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function updateObjects() 
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisualNNApp::updateObjects() {
	int lastLayerIndex = nn.m_layers.size() - 1;

	int count = 0;
	//run through the nn structure and create all of the objects
	for (int l = 0; l < lastLayerIndex; l++) {

		int length = glm::sqrt(nn.m_layers[l].m_neurons.size());

		for (int row = 0; row < length; row++) {
			for (int col = 0; col < length; col++) {

				//set color value to the activation level of the neuron, usually from 0.0 to 1.0
				float color = nn.m_layers[l].m_neurons[row * length + col].value;
				std::shared_ptr<Object> obj = nn.m_layers[l].m_neurons[row * length + col].m_Object;

				color = std::max<float>(color, 0.15);
				obj->m_Material->setAmbientColor(glm::vec4(color, color, color, 1.0));
				obj->m_Material->setDiffuseColor(glm::vec4(color, color, color, 1.0));
				obj->m_Material->setSpecularColor(glm::vec4(color, color, color, 1.0));
			}
		}
	}

	//update last layer 
	for (int i = 0; i < nn.m_layers[lastLayerIndex].m_neurons.size(); i++) {
		float color = nn.m_layers[lastLayerIndex].m_neurons[i].value;
		
		color = std::max<float>(color, 0.15);
		std::shared_ptr<Object> obj = nn.m_layers[lastLayerIndex].m_neurons[i].m_Object;
		obj->m_Material->setAmbientColor(glm::vec4(color, color, color, 1.0));
		obj->m_Material->setDiffuseColor(glm::vec4(color, color, color, 1.0));
		obj->m_Material->setSpecularColor(glm::vec4(color, color, color, 1.0));

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Cleanup()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisualNNApp::cleanup() {

	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Cleaning Up");
	m_thread->stop();
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Done!");

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function OnRightButtonDown()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void VisualNNApp::OnRightButtonDown(WPARAM wParam, LPARAM lParam) {

	GetCursorPos(&savemouse);
	SetCursorPos(m_ClientWidth / 2, m_ClientHeight / 2);   //reset mouse cursor to center of screen
	GetCursorPos(&currmouse);
	lastmouse = currmouse;
	ShowCursor(FALSE);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function OnRightButtonUp()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisualNNApp::OnRightButtonUp(WPARAM wParam, LPARAM lParam) {
	SetCursorPos(savemouse.x, savemouse.y);
	ShowCursor(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function OnKeyDown()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void VisualNNApp::OnKeyDown(WPARAM wParam, LPARAM lParam) {


	//toggle wirefame mode
	if (isKeyPressed('M')) {
		wireframemode = !wireframemode;
	}

	//toggle pausing the thread
	if (isKeyPressed('P')) {
		m_paused = !m_paused;
		if (m_paused)
			m_thread->stop();
		else
			m_thread->start();
	}

	//draw lines between the neurons
	if (isKeyPressed('C')) {
		m_drawconnections = !m_drawconnections;
	}

	//faster AI processing
	if (isKeyPressed('L')) {
		m_threadspeed -= 100;
		m_threadspeed = m_threadspeed < 0 ? 0 : m_threadspeed;
		m_thread->setspeed(m_threadspeed);
	}

	//slower AI processing
	if (isKeyPressed('K')) {
		m_threadspeed += 100;
		m_thread->setspeed(m_threadspeed);
	}

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function WinMain()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int cmdShow) {

	VisualNNApp app(hInstance, ipCmdLine, 1280, 768);
	return app.run();

}
