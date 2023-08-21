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

#include "texture.h"
#include "shader.h"
#include "shadercache.h"

class Material
{

public:
	Material();
	Material(std::string materialname);
	~Material();

	void bind();



	void setUniformFloat(const std::string& name, float val1);
	void setUniformFloat3(const std::string& name, float val1, float val2, float val3);
	void setUniformFloat3(const std::string &name, glm::vec3& vec);
	void setUniformFloat4(const std::string& name, glm::vec4& vec);		
	void setUniformMat4(const std::string& name, glm::mat4& mat);
	void setTexture(std::shared_ptr<Texture> texture) { m_Textures.clear(); m_Textures.push_back(texture); }


	void setAmbientColor(glm::vec3 color);
	void setDiffuseColor(glm::vec3 color);
	void setSpecularColor(glm::vec3 color);


	std::string m_MaterialName;
		
	std::shared_ptr<Shader> m_Shader;	
	std::vector<std::shared_ptr<Texture>> m_Textures;
	

	glm::vec4 m_AmbientColor;
	glm::vec4 m_DiffuseColor;
	glm::vec4 m_SpecularColor;


private:
	

};

