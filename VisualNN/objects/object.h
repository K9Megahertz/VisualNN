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
#include <vector>
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../renderer/material.h"
#include "../objects/mesh.h"
#include "modeltransform.h"
#include "meshgenerator.h"
#include "meshmanager.h"
#include "materialgenerator.h"
#include "../renderer/materialmanager.h"
#include "../renderer/texture.h"


class Object
{

public:

	virtual ~Object();

	unsigned int getVertexCount() { return (unsigned int)m_Mesh->m_Vertices.size() / 3; }
	unsigned int getIndexCount() { return (unsigned int)m_Mesh->m_Indices.size(); }
	unsigned int getTriangleCount() { return (unsigned int)m_Mesh->m_Indices.size() / 3; }
	const Vertex* getVertices() const { return &m_Mesh->m_Vertices[0]; }
	const unsigned int* getIndices() const { return &m_Mesh->m_Indices[0]; }

	void setMaterial(std::shared_ptr<Material> mat) { m_Material = mat; }
	std::shared_ptr<Material> getMaterial() { return m_Material; }
	

	void setPosition(glm::vec3 vec) { m_Transform.setPosition(vec); }
	glm::vec3 getPosition() { return m_Transform.getPosition(); }

	void setRotation(glm::vec3 vec) { m_Transform.setRotation(vec); }	
	glm::vec3 getRotation() { return m_Transform.getRotation(); }

	void setColor(glm::vec3 color) { m_Color = color; }

	void setScale(float scale) { setScale(glm::vec3(scale, scale, scale)); }
	void setScale(glm::vec3 vec) { m_Transform.setScale(vec); }
	
	
	std::shared_ptr<Mesh> getMesh() { return m_Mesh; }
	glm::vec3 getColor() { return m_Color; }
	glm::mat4 getModelMatrix() { return m_Transform.getModelMatrix(); }	

	ModelTransform m_Transform;
	glm::vec3 m_Color;
	std::shared_ptr<Mesh> m_Mesh;
	std::shared_ptr<Material> m_Material;		
	

	

protected:

	Object();
	
	
	
	
};

