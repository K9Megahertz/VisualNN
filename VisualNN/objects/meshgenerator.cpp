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

#include "meshgenerator.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function GenerateSphere()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Mesh> MeshGenerator::GenerateSphere(float radius, int slices, int rows) {

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("Sphere");
	

	const float PI = 3.1415926f;

	float x;
	float y;
	float z;



	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);

	//Vertices

	//top of sphere
	mesh->m_Vertices.push_back(Vertex({ {0, radius, 0}, {0, 1, 0}, color, {0, 0}, 0 }));


	float phiStep = PI / rows;
	float thetaStep = 2.0f * PI / slices;

	for (int i = 1; i <= rows - 1; i++) {
		float phi = i * phiStep;
		for (int j = 0; j < slices; j++) {
			float theta = j * thetaStep;
			x = radius * sinf(phi) * cosf(theta);
			y = radius * cosf(phi);
			z = -radius * sinf(phi) * sinf(theta);


			//set the normal and normalize it
			glm::vec3 n(x,y,z);			
			n = glm::normalize(n);

			//add the vertex to the mesh
			mesh->m_Vertices.push_back(Vertex({ {x, y, z}, {n.x, n.y, n.z}, color, {0, 0}, 0 }));

		}
	}

	//Bottom of sphere
	mesh->m_Vertices.push_back(Vertex({ {0, -radius, 0}, {0, -1, 0}, color, {0, 0}, 0 }));

	

	//Indices

	for (int k = 1; k < slices; k++) {
		mesh->m_Indices.push_back(0);
		mesh->m_Indices.push_back(k);
		mesh->m_Indices.push_back(k + 1);
	}

	mesh->m_Indices.push_back(0);
	mesh->m_Indices.push_back(slices);
	mesh->m_Indices.push_back(1);


	int baseIndex = 1;
	int ringVertexCount = slices + 1;
	for (int i = 0; i < rows - 2; i++) {
		for (int j = 0; j < slices - 1; j++) {
			mesh->m_Indices.push_back(baseIndex + i * slices + j);
			mesh->m_Indices.push_back(baseIndex + (i + 1) * slices + j + 1);
			mesh->m_Indices.push_back(baseIndex + i * slices + j + 1);

			mesh->m_Indices.push_back(baseIndex + i * slices + j);
			mesh->m_Indices.push_back(baseIndex + (i + 1) * slices + j);
			mesh->m_Indices.push_back(baseIndex + (i + 1) * slices + j + 1);

		}

		mesh->m_Indices.push_back(slices * (i + 1));
		mesh->m_Indices.push_back(slices * (i + 1) + 1);
		mesh->m_Indices.push_back(slices * i + 1);

		mesh->m_Indices.push_back(slices * (i + 1));
		mesh->m_Indices.push_back(slices * (i + 2));
		mesh->m_Indices.push_back(slices * (i + 1) + 1);


	}

	int southPoleIndex = (unsigned int)mesh->m_Vertices.size() * 6 / 6 - 1;
	baseIndex = southPoleIndex - (ringVertexCount - 1);

	for (int i = 0; i < slices - 1; i++) {
		mesh->m_Indices.push_back(southPoleIndex);
		mesh->m_Indices.push_back(baseIndex + i + 1);
		mesh->m_Indices.push_back(baseIndex + i);
	}

	mesh->m_Indices.push_back(southPoleIndex);
	mesh->m_Indices.push_back(southPoleIndex - (ringVertexCount - 1));
	mesh->m_Indices.push_back(southPoleIndex - 1);


	return mesh;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function GenerateCube()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::shared_ptr<Mesh> MeshGenerator::GenerateCube(float size) {

	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("Cube");
	
	//front surface
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size,  0.5 * size}, {0, 0, 1}, color, {0, 0}, 0 }));  //00
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size,  0.5 * size}, {0, 0, 1}, color, {1, 0}, 0 }));  //01
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size,  0.5 * size}, {0, 0, 1}, color, {1, 1}, 0 }));  //02
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size,  0.5 * size}, {0, 0, 1}, color, {0, 1}, 0 }));  //03
	
	//right surface
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size,  0.5 * size}, {1, 0, 0}, color, {0, 0}, 0 }));  //04
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size, -0.5 * size}, {1, 0, 0}, color, {1, 0}, 0 }));  //05
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size, -0.5 * size}, {1, 0, 0}, color, {1, 1}, 0 }));  //06
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size,  0.5 * size}, {1, 0, 0}, color, {0, 1}, 0 }));  //07
	
	//back surface
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size, -0.5 * size}, {0, 0, -1}, color, {0, 0}, 0 }));  //08
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size, -0.5 * size}, {0, 0, -1}, color, {1, 0}, 0 }));  //09
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size, -0.5 * size}, {0, 0, -1}, color, {1, 1}, 0 }));  //10
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size, -0.5 * size}, {0, 0, -1}, color, {0, 1}, 0 }));  //11
	
	//left surface
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size, -0.5 * size}, {-1, 0, 0}, color, {0, 0}, 0 }));  //12
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size,  0.5 * size}, {-1, 0, 0}, color, {1, 0}, 0 }));  //13
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size,  0.5 * size}, {-1, 0, 0}, color, {1, 1}, 0 }));  //14
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size, -0.5 * size}, {-1, 0, 0}, color, {0, 1}, 0 }));  //15
	
	//top surface
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size,  0.5 * size}, {0, 1, 0}, color, {0, 0}, 0 }));  //16
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size,  0.5 * size}, {0, 1, 0}, color, {1, 0}, 0 }));  //17
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size, -0.5 * size}, {0, 1, 0}, color, {1, 1}, 0 }));  //18
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size, -0.5 * size}, {0, 1, 0}, color, {0, 1}, 0 }));  //19
	
	//bottom surface
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size, -0.5 * size}, {0, -1, 0}, color, {0, 0}, 0 }));  //20
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size, -0.5 * size}, {0, -1, 0}, color, {1, 0}, 0 }));  //21
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size,  0.5 * size}, {0, -1, 0}, color, {1, 1}, 0 }));  //22
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size,  0.5 * size}, {0, -1, 0}, color, {0, 1}, 0 }));  //23



	mesh->m_Indices = {
		0, 1, 2, // Front face
		2, 3, 0,

		4, 5, 6, // Right face
		6, 7, 4,

		8, 9, 10, // Back face
		10, 11, 8,

		12, 13, 14, // Left face
		14, 15, 12,

		16, 17, 18, // Bottom face
		18, 19, 16,

		20, 21, 22, // Top face
		22, 23, 20
	};

	return mesh;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function GenerateTriangle()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::shared_ptr<Mesh> MeshGenerator::GenerateTriangle(float size) {

	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("Triangle");


	//top of triangle
	mesh->m_Vertices.push_back(Vertex({ {-0.5, -0.5, 0}, {0, 0, 1}, color, {0, 0}, 0 }));

	//right vert
	mesh->m_Vertices.push_back(Vertex({ {0.5, -0.5, 0}, {0, 0, 1}, color, {0, 0}, 0 }));

	//left vert
	mesh->m_Vertices.push_back(Vertex({ {0.0, 0.5, 0}, {0, 0, 1}, color, {0, 0}, 0 }));


	mesh->m_Indices = {
		0, 1, 2 // Front face
	};

	return mesh;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function GenerateQuad()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Mesh> MeshGenerator::GenerateQuad(float size) {

	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("Quad");

	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size, -0.5 * size,  0.5 * size}, {0, 0, 1}, color, {0, 0}, 0 }));  //00
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size, -0.5 * size,  0.5 * size}, {0, 0, 1}, color, {1, 0}, 0 }));  //01
	mesh->m_Vertices.push_back(Vertex({ { 0.5 * size,  0.5 * size,  0.5 * size}, {0, 0, 1}, color, {1, 1}, 0 }));  //02
	mesh->m_Vertices.push_back(Vertex({ {-0.5 * size,  0.5 * size,  0.5 * size}, {0, 0, 1}, color, {0, 1}, 0 }));  //03

	mesh->m_Indices = {
		0, 1, 2, // Front face
		2, 3, 0,
	};

	return mesh;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function GenerateTriforce()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Mesh> MeshGenerator::GenerateTriforce(float size) {

	glm::vec3 color = glm::vec3(static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX);

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("Triforce");


	//front of triforce
	mesh->m_Vertices.push_back(Vertex({ { 0.000,  0.866,  0.1}, {0.000, 0.000, 1.000}, color, {0.5, 1}, 0 }));         //00 - top front	
	mesh->m_Vertices.push_back(Vertex({ {-0.866, -0.500,  0.1}, {0.000, 0.000, 1.000}, color, {0, 0}, 0 }));         //01 - bottom left front	
	mesh->m_Vertices.push_back(Vertex({ { 0.866, -0.500,  0.1}, {0.000, 0.000, 1.000}, color, {1, 0}, 0 }));         //02 - bottom right front

	//top slant on right
	mesh->m_Vertices.push_back(Vertex({ { 0.000,  0.866,  0.1}, { 0.866, 0.500, 0.000}, color, {0, 0}, 0 }));         //03 - top front	
	mesh->m_Vertices.push_back(Vertex({ { 0.866, -0.500,  0.1}, { 0.866, 0.500, 0.000}, color, {1, 0}, 0 }));         //04 - bottom right front
	mesh->m_Vertices.push_back(Vertex({ { 0.866, -0.500, -0.1}, { 0.866, 0.500, 0.000}, color, {1, 1}, 0 }));         //05 - bottom right back
	mesh->m_Vertices.push_back(Vertex({ { 0.000,  0.866, -0.1}, { 0.866, 0.500, 0.000}, color, {0, 1}, 0 }));         //06 - top back

	//top slant on left
	mesh->m_Vertices.push_back(Vertex({ { 0.000,  0.866, -0.1}, {-0.866, 0.500, 0.000}, color, {0, 0}, 0 }));         //07 - top back	
	mesh->m_Vertices.push_back(Vertex({ {-0.866, -0.500, -0.1}, {-0.866, 0.500, 0.000}, color, {1, 0}, 0 }));         //08 - bottom left back
	mesh->m_Vertices.push_back(Vertex({ {-0.866, -0.500,  0.1}, {-0.866, 0.500, 0.000}, color, {1, 1}, 0 }));         //09 - bottom left front
	mesh->m_Vertices.push_back(Vertex({ { 0.000,  0.866,  0.1}, {-0.866, 0.500, 0.000}, color, {0, 1}, 0 }));         //10 - top front

	//bottom
	mesh->m_Vertices.push_back(Vertex({ { 0.866, -0.500,  0.1}, { 0.000, -1.000, 0.000}, color, {0, 0}, 0 }));         //11 - bottom right front	
	mesh->m_Vertices.push_back(Vertex({ {-0.866, -0.500,  0.1}, { 0.000, -1.000, 0.000}, color, {1, 0}, 0 }));         //12 - bottom left front
	mesh->m_Vertices.push_back(Vertex({ {-0.866, -0.500, -0.1}, { 0.000, -1.000, 0.000}, color, {1, 1}, 0 }));         //13 - bottom left back
	mesh->m_Vertices.push_back(Vertex({ { 0.866, -0.500, -0.1}, { 0.000, -1.000, 0.000}, color, {0, 1}, 0 }));         //14 - bottom right back
	
	//back
	mesh->m_Vertices.push_back(Vertex({ { 0.000,  0.866, -0.1}, { 0.000, 0.000, -1.000}, color, {0.5, 1}, 0 }));       //15 - top back	
	mesh->m_Vertices.push_back(Vertex({ { 0.866, -0.500, -0.1}, { 0.000, 0.000, -1.000}, color, {0, 0}, 0 }));         //16 - bottom right back
	mesh->m_Vertices.push_back(Vertex({ {-0.866, -0.500, -0.1}, { 0.000, 0.000, -1.000}, color, {1, 0}, 0 }));         //17 - bottom left back	


	mesh->m_Indices = {
		0, 1, 2,     // Front face

		3, 4, 5,     //top slant on right
		5, 6, 3,

		7, 8, 9,     //top slant on left
		9, 10, 7,

		11, 12, 13,  //bottom
		13, 14, 11,

		15,16,17     //back
	};

	return mesh;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function GenerateTorus()
//  TODO: Need to fix
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Mesh> MeshGenerator::GenerateTorus(float radius, float tubeRadius, int segments, int sides) {	

	glm::vec3 color = glm::vec3(static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX);

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("Torus");

	float thetaStep = glm::two_pi<float>() / sides;
	float phiStep = glm::two_pi<float>() / segments;

	for (int i = 0; i <= sides; ++i) {
		float theta = i * thetaStep;
		glm::vec3 tangent = glm::vec3(std::cos(theta), std::sin(theta), 0.0f);

		for (int j = 0; j <= segments; ++j) {
			float phi = j * phiStep;
			glm::vec3 position = glm::vec3(
				(radius + tubeRadius * std::cos(phi)) * std::cos(theta),
				(radius + tubeRadius * std::cos(phi)) * std::sin(theta),
				tubeRadius * std::sin(phi)
			);

			glm::vec3 normal = glm::normalize(position - glm::vec3(
				std::cos(theta) * (radius + tubeRadius * std::cos(phi)),
				std::sin(theta) * (radius + tubeRadius * std::cos(phi)),
				0.0f
			));

			mesh->m_Vertices.push_back({ position, normal });
		}
	}

	for (int i = 0; i < sides; ++i) {
		for (int j = 0; j < segments; ++j) {
			int currentRow = i * (segments + 1);
			int nextRow = (i + 1) * (segments + 1);

			mesh->m_Indices.push_back(currentRow + j);
			mesh->m_Indices.push_back(nextRow + j);
			mesh->m_Indices.push_back(currentRow + j + 1);

			mesh->m_Indices.push_back(currentRow + j + 1);
			mesh->m_Indices.push_back(nextRow + j);
			mesh->m_Indices.push_back(nextRow + j + 1);
		}
	}


	return mesh;
}