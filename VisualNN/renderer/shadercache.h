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
#include <unordered_map>
#include <string>
#include <memory>
#include "shader.h"

class ShaderCache {
public:
    static ShaderCache &getInstance() {
        static ShaderCache instance;
        return instance;
    }

    ShaderCache(const ShaderCache &) = delete;
    ShaderCache &operator=(const ShaderCache &) = delete;

    std::shared_ptr<Shader> getShader(const std::string &name) {
        auto iter = m_Shaders.find(name);
        if (iter != m_Shaders.end()) {
            return iter->second;
        }

        std::shared_ptr<Shader> shader;
        shader = std::make_shared<Shader>("shaders/" + name + ".vert", "shaders/" + name + ".frag");        

        m_Shaders[name] = shader;
        return shader;
    }   

private:
    ShaderCache() = default;

    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};