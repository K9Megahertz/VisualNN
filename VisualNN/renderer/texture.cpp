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

#include "texture.h"
#include "../vendor/stb_image.h"


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

Texture::Texture(const std::string &path) {

	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	m_Width = width;
	m_Height = height;


	glCreateTextures(GL_TEXTURE_2D, 1, &m_ID); GLError::GLCheckError();
	glTextureStorage2D(m_ID, 1, GL_RGB8, m_Width, m_Height); GLError::GLCheckError();

	glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GLError::GLCheckError();
	glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GLError::GLCheckError();

	if (channels == 4)
		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data); 
	else
		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data); 
	
	GLError::GLCheckError();

}

Texture::~Texture() {
		glDeleteTextures(1, &m_ID); GLError::GLCheckError();
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

void Texture::bind(unsigned int slot) {
	glBindTextureUnit(slot, m_ID);
}


