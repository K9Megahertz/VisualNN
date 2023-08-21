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

#include <GL/glew.h>       //Must come before glfw3.h

#include <GLM/vec3.hpp> // glm::vec3
#include <GLM/vec4.hpp> // glm::vec4
#include <GLM/mat4x4.hpp> // glm::mat4
#include <GLM/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <GLM/gtc/type_ptr.hpp>  //glm::value_ptr

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../util/logger.h"
#include "glerror.h"



class Shader
{


public:


    Shader(std::string vertextShader, std::string fragmentShader);
    Shader();
    ~Shader();

    void bind();
    int getAttribLocation(std::string attribute);
    int getUniformLocation(std::string name);
    int getProgram();

    void setUniformInt(const std::string& name, int val);
    void setUniformFloat(const std::string& name, float val1);
    void setUniformFloat2(const std::string& name, float val, float val2);
    void setUniformFloat3(const std::string& name, float val1, float val2, float val3);
    void setUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4);
    void setUniformFloat4(const std::string& name, glm::vec4& vec);
    void setUniformMat3(const std::string& name, glm::mat3& mat);
    void setUniformMat4(const std::string& name, glm::mat4& mat);


private:

    void readFile(std::string shaderFileName, std::string& shaderSource);
    bool initShaders(std::string vShaderSource, std::string fShaderSource, int& program);
    int createProgram(std::string vShader, std::string fShader);
    int loadShader(GLenum shaderType, std::string shaderSource);   


    int m_program;

};





