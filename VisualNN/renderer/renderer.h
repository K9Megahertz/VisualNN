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

#include <GL/glew.h>       //Must come before glfw3.h

#include <GLM/vec3.hpp> // glm::vec3
#include <GLM/vec4.hpp> // glm::vec4
#include <GLM/mat4x4.hpp> // glm::mat4
#include <GLM/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <GLM/gtc/type_ptr.hpp>  //glm::value_ptr

#include "../objects/mesh.h"
#include "material.h"
#include "texture.h"
#include "buffers/vertexarray.h"
#include "buffers/vertexbuffer.h"
#include "buffers/indexbuffer.h"
#include "instancegroup.h"
#include "linegroup.h"
#include "materialmanager.h"
#include "texturemanager.h"
#include "../objects/meshmanager.h"
#include "../objects/materialgenerator.h"



//class InstanceGroup;

#pragma once
class Renderer
{


public:

	Renderer();
	~Renderer();
	static void submitMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, glm::mat4 modelMatrix);
	static void submitMeshBatched(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, glm::mat4 modelMatrix);	
	static void submitMeshInstanced(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, glm::mat4 modelMatrix);	
	static void SubmitLine(Vertex v0, Vertex v1, std::shared_ptr<Material> material);
	static void setWireFrame(bool flag);
	static void clear(glm::vec3 color);
	static void begin(glm::mat4 matrixView, glm::mat4 matrixProjection);
	static void end();
	static bool init();		

	static const unsigned int MaxVertexCount;
	static const unsigned int MaxIndexCount;
	static const unsigned int MaxInstanceCount;

	
private:

	static VertexArray* m_VAO;
	static VertexBuffer* m_VBO;
	static IndexBuffer* m_IBO;

	static VertexArray *m_batchVAO;
	static VertexBuffer *m_batchVBO;
	static IndexBuffer *m_batchIBO;	

	static VertexArray *m_instanceVAO;
	static VertexBuffer *m_instanceVBO;
	static IndexBuffer *m_instanceIBO;
	static InstanceBuffer *m_instanceNBO;

	static VertexArray *m_lineVAO;
	static VertexBuffer *m_lineVBO;

	static bool m_initialized;

	static glm::mat4 m_matrixView;
	static glm::mat4 m_matrixProjection;

	static std::vector<InstanceGroup*> m_InstanceGroups;
	static std::vector<LineGroup*> m_LineGroups;
	

	static void beginBatches();
	static void endBatches();

	static void beginLines();
	static void endLines();

	static void beginInstances();
	static void endInstances();

	


	


};

