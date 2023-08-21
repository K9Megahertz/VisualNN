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
#include <gl/glew.h>

#include <GLM/vec3.hpp> // glm::vec3
#include <GLM/vec4.hpp> // glm::vec4
#include <GLM/mat4x4.hpp> // glm::mat4
#include <GLM/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <cstddef>
#include "../glerror.h"
#include "../texture.h"

struct InstanceAttributes {

    glm::mat4 modelMatrix;
    glm::vec4 modelAmbientColor;
    glm::vec4 modelDiffuseColor;    
    //glm::vec4 modelSpecularColor;

};


class InstanceBuffer {

public:

    
    InstanceBuffer(std::vector<glm::mat4> modelMatrices, unsigned int numbytes);
    InstanceBuffer(unsigned int numbytes);        
    ~InstanceBuffer();

    void setData();

    void bind();
    void unbind();

    void pushInstanceAttributes(InstanceAttributes ia);
    void pushInstanceAttributesSet(std::vector<InstanceAttributes> ia);

    std::vector<InstanceAttributes> getAttributes();
    void reset();

private:

    unsigned int m_numInstances;
    std::vector<InstanceAttributes> m_InstanceAttributes;

    GLuint m_id;
};

