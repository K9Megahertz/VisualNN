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
#include "meshgenerator.h"

class MeshManager {
public:
    static MeshManager &getInstance() {
        static MeshManager instance;
        return instance;
    }

    MeshManager(const MeshManager &) = delete;
    MeshManager &operator=(const MeshManager &) = delete;

    std::shared_ptr<Mesh> getMesh(const std::string &name) {
        auto iter = m_Meshes.find(name);
        if (iter != m_Meshes.end()) {
            return iter->second;
        }

        std::shared_ptr<Mesh> mesh;
        // Mesh doesn't exist, create it
        //std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(name);
        if (name == "Sphere")
            mesh = MeshGenerator::GenerateSphere(1, 32, 32);
        if (name == "Cube")
            mesh = MeshGenerator::GenerateCube(1);
        if (name == "Triangle")
            mesh = MeshGenerator::GenerateTriangle(1);
        if (name == "Triforce")
            mesh = MeshGenerator::GenerateTriforce(1);
        if (name == "Torus")
            mesh = MeshGenerator::GenerateTorus(1, 0.25, 32, 32);
        if (name == "Quad")
            mesh = MeshGenerator::GenerateQuad(1);

        m_Meshes[name] = mesh;
        return mesh;
    }

    /*std::shared_ptr<Material> GetMaterial(const std::string &name) {
        std::unordered_map<std::string, std::shared_ptr<Material>>::iterator iter = m_Materials.find(name);
        if (iter == m_Materials.end()) {
            return nullptr;
        }
        return iter->second;
    }*/

private:
    MeshManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Mesh>> m_Meshes;
};