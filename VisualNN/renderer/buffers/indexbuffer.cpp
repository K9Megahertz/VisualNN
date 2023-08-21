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

#include "indexbuffer.h"


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

IndexBuffer::IndexBuffer(std::vector<unsigned int> indices, unsigned int count) : m_numIndices(count) {

    pushIndices(indices, 0);
    glGenBuffers(1, &m_id); GLError::GLCheckError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); GLError::GLCheckError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); GLError::GLCheckError();
    unbind(); GLError::GLCheckError();
    Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "  Generated Index Buffer with id: " + std::to_string(m_id));

}

IndexBuffer::IndexBuffer(unsigned int count) : m_numIndices(0) {

    glGenBuffers(1, &m_id); GLError::GLCheckError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); GLError::GLCheckError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, GL_STATIC_DRAW); GLError::GLCheckError();
    unbind(); GLError::GLCheckError();
    Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "  Generated Index Buffer with id: " + std::to_string(m_id));

}

IndexBuffer::~IndexBuffer() {

    Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "  Deleting Index Buffer with id: " + std::to_string(m_id));
    glDeleteBuffers(1, &m_id);

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function bind()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IndexBuffer::bind() {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, getIndices().size() * sizeof(unsigned int), (const void*)getIndices().data()); GLError::GLCheckError();

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function unbind()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IndexBuffer::unbind() {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function getCount()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int IndexBuffer::getCount() {

    return m_numIndices;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function pushIndices()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IndexBuffer::pushIndices(std::vector<unsigned int> indices, int offset) {
    
    std::vector<unsigned int> modifiedindices = indices;
    std::transform(modifiedindices.begin(), modifiedindices.end(), modifiedindices.begin(), [offset](int i) { return i + offset; });
    
    m_indices.insert(m_indices.end(), modifiedindices.begin(), modifiedindices.end());
    m_numIndices += modifiedindices.size();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function getIndices()
//  
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned int> IndexBuffer::getIndices() {

    return m_indices;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function reset()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IndexBuffer::reset() {

    m_numIndices = 0;
    m_indices.clear();

}

