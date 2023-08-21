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

#include "vertexbuffer.h"


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


VertexBuffer::VertexBuffer(std::vector<Vertex> vertices, unsigned int numbytes) {

    m_vertices.reserve(100000);
    //TODO: I think i wanna push the verts here too? Fix later
    pushVertices(vertices);
    glGenBuffers(1, &m_id); GLError::GLCheckError();
    glBindBuffer(GL_ARRAY_BUFFER, m_id); GLError::GLCheckError();
    glBufferData(GL_ARRAY_BUFFER, numbytes * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); GLError::GLCheckError();

    glEnableVertexAttribArray(0); GLError::GLCheckError();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, m_Position)); GLError::GLCheckError();

    glEnableVertexAttribArray(1); GLError::GLCheckError();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, m_Normal)); GLError::GLCheckError();

    glEnableVertexAttribArray(2); GLError::GLCheckError();
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, m_Color)); GLError::GLCheckError();

    glEnableVertexAttribArray(3); GLError::GLCheckError();
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, m_TexCoords)); GLError::GLCheckError();

    glEnableVertexAttribArray(4); GLError::GLCheckError();
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, m_texIndex)); GLError::GLCheckError();

    unbind(); GLError::GLCheckError();

    Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "  Generated Vertex Buffer with id: " + std::to_string(m_id));
}

VertexBuffer::VertexBuffer(unsigned int numbytes) {

    m_vertices.reserve(100000);

    glGenBuffers(1, &m_id); GLError::GLCheckError();
    glBindBuffer(GL_ARRAY_BUFFER, m_id); GLError::GLCheckError();
    glBufferData(GL_ARRAY_BUFFER, numbytes, nullptr, GL_STATIC_DRAW); GLError::GLCheckError();

    glEnableVertexAttribArray(0); GLError::GLCheckError();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Position)); GLError::GLCheckError();

    glEnableVertexAttribArray(1); GLError::GLCheckError();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Normal)); GLError::GLCheckError();

    glEnableVertexAttribArray(2); GLError::GLCheckError();
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Color)); GLError::GLCheckError();

    glEnableVertexAttribArray(3); GLError::GLCheckError();
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_TexCoords)); GLError::GLCheckError();

    glEnableVertexAttribArray(4); GLError::GLCheckError();
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_texIndex)); GLError::GLCheckError();

    unbind(); GLError::GLCheckError();

    Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "  Generated Vertex Buffer with id: " + std::to_string(m_id));
}

VertexBuffer::~VertexBuffer() {
    Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "  Deleting Vertex Buffer with id: " + std::to_string(m_id));
    glDeleteBuffers(1, &m_id); GLError::GLCheckError();
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

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);    
    setData();
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function setData()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VertexBuffer::setData() {
    int count = getVertices().size();
    std::vector<Vertex> blah = getVertices();
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, getVertices().size() * sizeof(Vertex), (const void *)getVertices().data()); GLError::GLCheckError();

    
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

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function pushVertices()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


unsigned int VertexBuffer::pushVertices(std::vector<Vertex> verts) {

    unsigned int returnoffset = m_numVertices;
    m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());
    m_numVertices += verts.size();
    return returnoffset;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function pushVertex()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


unsigned int VertexBuffer::pushVertex(Vertex vert) {

    unsigned int returnoffset = m_numVertices;
    m_vertices.push_back(vert);    
    m_numVertices ++;
    return returnoffset;

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


void VertexBuffer::reset() {
    m_numVertices = 0;
    m_vertices.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function getVertices()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Vertex> VertexBuffer::getVertices() {
    return m_vertices;
}