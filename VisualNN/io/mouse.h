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
#include <Windows.h>

class Mouse {
public:
    Mouse() : m_left(false), m_right(false), m_x(0), m_y(0) {}

    bool isLeftMousePressed() const { return m_left; }
    bool isRightMousePressed() const { return m_right; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    void OnLeftButtonDown(WPARAM wParam, LPARAM lParam) {
        m_left = true;
        UpdatePosition(lParam);
    }

    void OnLeftButtonUp() {
        m_left = false;
    }

    void OnRightButtonDown(WPARAM wParam, LPARAM lParam) {
        m_right = true;
        UpdatePosition(lParam);
    }

    void OnRightButtonUp() {
        m_right = false;
    }

    void OnMouseMove(LPARAM lParam) {
        UpdatePosition(lParam);
    }

private:
    bool m_left;
    bool m_right;
    int m_x;
    int m_y;

    void UpdatePosition(LPARAM lParam) {
        m_x = LOWORD(lParam);
        m_y = HIWORD(lParam);
    }
};